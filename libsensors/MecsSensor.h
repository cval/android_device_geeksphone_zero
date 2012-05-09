/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_MECS_SENSOR_H
#define ANDROID_MECS_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/ioctl.h>
#include <sys/types.h>


#include "nusensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"

/*****************************************************************************/

/* Use 'e' as magic number */
#define ECOMPASS_IOM	'e'

/* IOCTLs for ECOMPASS device */
#define ECOMPASS_IOC_SET_MODE		_IOW(ECOMPASS_IOM, 0x00, short)
#define ECOMPASS_IOC_SET_DELAY		_IOW(ECOMPASS_IOM, 0x01, short)
#define ECOMPASS_IOC_GET_DELAY		_IOR(ECOMPASS_IOM, 0x02, short)

#define ECOMPASS_IOC_SET_AFLAG		_IOW(ECOMPASS_IOM, 0x10, short)
#define ECOMPASS_IOC_GET_AFLAG		_IOR(ECOMPASS_IOM, 0x11, short)
#define ECOMPASS_IOC_SET_MFLAG		_IOW(ECOMPASS_IOM, 0x12, short)
#define ECOMPASS_IOC_GET_MFLAG		_IOR(ECOMPASS_IOM, 0x13, short)
#define ECOMPASS_IOC_SET_OFLAG		_IOW(ECOMPASS_IOM, 0x14, short)
#define ECOMPASS_IOC_GET_OFLAG		_IOR(ECOMPASS_IOM, 0x15, short)
#define ECOMPASS_IOC_SET_PFLAG		_IOW(ECOMPASS_IOM, 0x16, short)
#define ECOMPASS_IOC_GET_PFLAG		_IOR(ECOMPASS_IOM, 0x17, short)
#define ECOMPASS_IOC_SET_LFLAG		_IOW(ECOMPASS_IOM, 0x18, short)
#define ECOMPASS_IOC_GET_LFLAG		_IOR(ECOMPASS_IOM, 0x19, short)

#define ECOMPASS_IOC_SET_APARMS		_IOW(ECOMPASS_IOM, 0x20, int[4])
#define ECOMPASS_IOC_GET_APARMS		_IOR(ECOMPASS_IOM, 0x21, int[4])
#define ECOMPASS_IOC_SET_MPARMS		_IOW(ECOMPASS_IOM, 0x22, int[4])
#define ECOMPASS_IOC_GET_MPARMS		_IOR(ECOMPASS_IOM, 0x23, int[4])
#define ECOMPASS_IOC_SET_OPARMS_YAW	_IOW(ECOMPASS_IOM, 0x24, int[4])
#define ECOMPASS_IOC_GET_OPARMS_YAW	_IOR(ECOMPASS_IOM, 0x25, int[4])
#define ECOMPASS_IOC_SET_OPARMS_PITCH	_IOW(ECOMPASS_IOM, 0x26, int[4])
#define ECOMPASS_IOC_GET_OPARMS_PITCH	_IOR(ECOMPASS_IOM, 0x27, int[4])
#define ECOMPASS_IOC_SET_OPARMS_ROLL	_IOW(ECOMPASS_IOM, 0x28, int[4])
#define ECOMPASS_IOC_GET_OPARMS_ROLL	_IOR(ECOMPASS_IOM, 0x29, int[4])

#define ECOMPASS_IOC_SET_YPR		_IOW(ECOMPASS_IOM, 0x30, int[12])

/*****************************************************************************/

struct input_event;

class MecsSensor : public SensorBase {
public:
	MecsSensor();
	virtual ~MecsSensor();

	enum {
		Accelerometer = 0,
		MagneticField,
		Orientation,
		Proximity,
		Light,
        	numSensors
	};

	virtual int setDelay(int32_t handle, int64_t ns);
	virtual int enable(int32_t handle, int enabled);
	virtual int readEvents(sensors_event_t* data, int count);
	void processEvent(int code, int value);

private:
	int update_delay();
	uint32_t mEnabled;
	uint32_t mPendingMask;
	InputEventCircularReader mInputReader;
	sensors_event_t mPendingEvents[numSensors];
	uint64_t mDelays[numSensors];
};

/*****************************************************************************/

#endif  // ANDROID_MECS_SENSOR_H
