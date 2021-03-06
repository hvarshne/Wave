/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTLOADOPERATIONALDATAWORKER_H
#define WAVEMANAGEDOBJECTLOADOPERATIONALDATAWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveLoadOperationalDataForManagedObjectObjectManagerMessage;
class LoadOperationalDataContext;
class WaveManagedObjectLoadOperationalDataContext;

class WaveManagedObjectLoadOperationalDataWorker : public WaveWorker
{
    private :
        virtual WaveMessage *createMessageInstance                          (const UI32 &operationCode);

                void          loadOperationalDataHandler                     (WaveLoadOperationalDataForManagedObjectObjectManagerMessage *pWaveLoadOperationalDataForManagedObjectObjectManagerMessage);
                void          loadOperationalDataQueryManagedObjectStep      (LoadOperationalDataContext *pLoadOperationalDataContext);
                void          loadOperationalDataLoadStep                    (LoadOperationalDataContext *pLoadOperationalDataContext);
                void          loadOperationalDataLoadCallback                (WaveManagedObjectLoadOperationalDataContext *pWaveManagedObjectLoadOperationalDataContext);
                void          loadOperationalDataUpdateWaveManagedObjectStep (LoadOperationalDataContext *pLoadOperationalDataContext);

    protected :
    public :
         WaveManagedObjectLoadOperationalDataWorker (WaveObjectManager *pWaveObjectManager);
        ~WaveManagedObjectLoadOperationalDataWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTLOADOPERATIONALDATAWORKER_H
