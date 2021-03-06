/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Redundancy/RedundancyOptimizer64.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Mathematics/Z2/MultiByteWord.h"

#include <fstream>
#include <zlib.h>

namespace WaveNs
{

RedundancyOptimizer64::RedundancyOptimizer64 ()
    : RedundancyOptimizerBase ()
{
    MultiByteWord tempPolynomial;

    tempPolynomial.setPolynomialDegree (63);

    tempPolynomial[0] = 0xbf378d83;
    tempPolynomial[1] = 0x37e6b8a5;

    m_z2.setCurrentIrreduciblePolynomial (tempPolynomial);
}

RedundancyOptimizer64::~RedundancyOptimizer64 ()
{
    destroyUniqueChunks ();
}

void RedundancyOptimizer64::destroyUniqueChunks ()
{
    map<UI64, FixedSizeBuffer *>::iterator  element     = m_uniqueChunks.begin ();
    map<UI64, FixedSizeBuffer *>::iterator  endElement  = m_uniqueChunks.end ();
    FixedSizeBuffer                        *pTempBuffer = NULL;

    while (element != endElement)
    {
        pTempBuffer = element->second;

        if (NULL != pTempBuffer)
        {
            delete[] (pTempBuffer->getPRawBuffer ());
            delete pTempBuffer;
        }

        element++;
    }

    m_uniqueChunks.clear ();
    m_uniqueChunkCounts.clear ();
}

void RedundancyOptimizer64::optimizeFile (const string &fileName)
{
    ifstream       inputFileStream;
    char          *pBuffer                          = NULL; 
    UI64           fingerPrint;
    UI64           readLength                       = 0;
    UI64           i                                = 0;
    UI64           numberOfFixedChunks              = 0;
    UI64           residueSizeFromPreviousRead      = 0;
    UI64           j                                = 0;
    char          *pResidueBuffer                   = NULL;
    UI64           paddingRequiredToCompleteResidue = 0;
    UI64           paddedResidueSize                = 0;
    char          *pTempBuffer                      = NULL;
    char          *pFixedChunkSizeBuffer            = NULL;

    inputFileStream.open (fileName.c_str (), ios::binary);

    if (!inputFileStream)
    {
        //trace (TRACE_LEVEL_ERROR, "RedundancyOptimizer64::optimizeFile : File (" + fileName + ") cannot be opened to read.");
        //cerr << "RedundancyOptimizer64::optimizeFile : File (" + fileName + ") cannot be opened to read." << endl;
        return;
    }

    // Allocate buffer just before use.
    pBuffer                          = new char[m_fileIoSize];

    while (! (inputFileStream.eof ()))
    {
        pTempBuffer = pBuffer;

        waveAssert (NULL != pBuffer, __FILE__, __LINE__);

        inputFileStream.read (pBuffer, m_fileIoSize);
        readLength = inputFileStream.gcount ();

        if (residueSizeFromPreviousRead > 0)
        {
            paddingRequiredToCompleteResidue = m_fixedChunksize - residueSizeFromPreviousRead;

            if (readLength >= paddingRequiredToCompleteResidue)
            {
                paddedResidueSize = m_fixedChunksize;
                readLength -= paddingRequiredToCompleteResidue;
                pTempBuffer = pBuffer + paddingRequiredToCompleteResidue;

                memcpy (pResidueBuffer + residueSizeFromPreviousRead, pBuffer, paddingRequiredToCompleteResidue);
            }
            else
            {
                paddedResidueSize = residueSizeFromPreviousRead + readLength;
                readLength = 0;
                pTempBuffer = pTempBuffer + readLength;

                memcpy (pResidueBuffer + residueSizeFromPreviousRead, pBuffer, readLength);
            }

            m_z2.computeFingerPrintOptimizedFor64 (fingerPrint, pResidueBuffer, paddedResidueSize);

            addUniqueChunk (fingerPrint, pResidueBuffer, paddedResidueSize);

            pResidueBuffer = NULL;
        }

        numberOfFixedChunks         = readLength / m_fixedChunksize;
        residueSizeFromPreviousRead = readLength % m_fixedChunksize;

        for (i = 0, j = 0; i < numberOfFixedChunks; i++, j += m_fixedChunksize)
        {
            pFixedChunkSizeBuffer = new char[m_fixedChunksize];

            memcpy (pFixedChunkSizeBuffer, pTempBuffer + j, m_fixedChunksize);

            m_z2.computeFingerPrintOptimizedFor64 (fingerPrint, pFixedChunkSizeBuffer, m_fixedChunksize);

            addUniqueChunk (fingerPrint, pFixedChunkSizeBuffer, m_fixedChunksize);
        }

        if (0 < residueSizeFromPreviousRead)
        {
            pResidueBuffer = new char[m_fixedChunksize];
            memcpy (pResidueBuffer, pBuffer + j, residueSizeFromPreviousRead);
        }
    }

    if (pResidueBuffer != NULL)
    {
        m_z2.computeFingerPrintOptimizedFor64 (fingerPrint, pResidueBuffer, residueSizeFromPreviousRead);
        addUniqueChunk (fingerPrint, pResidueBuffer, residueSizeFromPreviousRead);
    }

    delete[] pBuffer;
}

void RedundancyOptimizer64::addUniqueChunk (const UI64 &fingerPrint, char *pBuffer, const UI64 &length)
{
          map<UI64, FixedSizeBuffer *>::iterator  element            = m_uniqueChunks.find (fingerPrint);
          map<UI64, FixedSizeBuffer *>::iterator  endElement         = m_uniqueChunks.end ();
          char                                   *pCompressedBuffer  = NULL;
          int                                     result             = 0;
    const UI64                                    compressedLength   = 2 * m_fixedChunksize;
          uLong                                   destinationLength  = compressedLength;

    if (element == endElement)
    {
        if (true == (getEnableCompression ()))
        {
            pCompressedBuffer  = new char[compressedLength];

            result = compress ((Bytef *) pCompressedBuffer, &destinationLength, (Bytef *) pBuffer, length);

            if (result == Z_OK)
            {
                if (destinationLength <= length)
                {
                    if (true == m_storeUniqueChunkData)
                    {
                        m_uniqueChunks[fingerPrint] = new FixedSizeBuffer (destinationLength, pCompressedBuffer, true);
                    }
                    else
                    {
                        m_uniqueChunks[fingerPrint] = NULL;
                        delete[] pCompressedBuffer;
                    }

                    m_uniqueChunkCounts[fingerPrint] = 1;

                    m_optimizedCompressedSize += destinationLength;
                    delete[] pBuffer;
                }
                else
                {
                    if (true == m_storeUniqueChunkData)
                    {
                        m_uniqueChunks[fingerPrint] = new FixedSizeBuffer (length, pBuffer, true);
                    }
                    else
                    {
                        m_uniqueChunks[fingerPrint] = NULL;
                        delete[] pBuffer;
                    }

                    m_uniqueChunkCounts[fingerPrint] = 1;

                    m_optimizedCompressedSize += length;
                    delete[] pCompressedBuffer;
                }
            }
            else
            {
                if (true == m_storeUniqueChunkData)
                {
                    m_uniqueChunks[fingerPrint] = new FixedSizeBuffer (length, pBuffer, true);
                }
                else
                {
                    m_uniqueChunks[fingerPrint] = NULL;
                    delete[] pBuffer;
                }

                m_uniqueChunkCounts[fingerPrint] = 1;

                m_optimizedCompressedSize += length;
                delete[] pCompressedBuffer;
                //trace (TRACE_LEVEL_ERROR, "RedundancyOptimizer64::addUniqueChunk : Coud not compress.");
            }
        }
        else
        {
            if (true == m_storeUniqueChunkData)
            {
                m_uniqueChunks[fingerPrint] = new FixedSizeBuffer (length, pBuffer, true);
            }
            else
            {
                m_uniqueChunks[fingerPrint] = NULL;
                delete[] pBuffer;
            }

            m_uniqueChunkCounts[fingerPrint] = 1;

            m_optimizedCompressedSize += length;
        }

        m_optimizedSize += length;
        m_totalNumberOfUniqueChunks++;
    }
    else
    {
        (m_uniqueChunkCounts[fingerPrint])++;
        delete[] pBuffer;
    }

    m_originalSize += length;
    m_totalNumberOfChunks++;
}

void RedundancyOptimizer64::print ()
{
    map<UI64, FixedSizeBuffer *>::iterator  element       = m_uniqueChunks.begin ();
    map<UI64, FixedSizeBuffer *>::iterator  endElement    = m_uniqueChunks.end ();
    FixedSizeBuffer                        *pTempBuffer   = NULL;
    string                                  bufferString;

    while (element != endElement)
    {
        pTempBuffer = element->second;

        pTempBuffer->toString (bufferString);

        //trace (TRACE_LEVEL_INFO, element->first + " : " + m_uniqueChunkCounts[element->first] + " : " + bufferString);
        //cout <<  element->first + " : " + m_uniqueChunkCounts[element->first] + " : " + bufferString << endl;
        cout <<  element->first + " : " + m_uniqueChunkCounts[element->first] << endl;

        element++;
    }

}

}
