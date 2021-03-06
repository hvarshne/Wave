/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu                                                 *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTTYPES_H
#define WAVEPOSTBOOTTYPES_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{
typedef	struct  postbootTableEntry {
		string	passName;
		vector  <WaveServiceId> serviceId;
        vector  <int> recoveryType; // 1:1 mapping from serviceId and it's recoveryType. recoveryType is a bitmap to contain COLD, WARM, etc
} postbootPass;

}

#endif // WAVEPOSTBOOTAGENT_H
