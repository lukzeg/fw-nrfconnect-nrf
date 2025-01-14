/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#pragma once

#include <platform/CHIPDeviceLayer.h>

#include <zephyr.h>

typedef void (*DFUOverSMPRestartAdvertisingHandler)(void);

class DFUOverSMP {
public:
	void Init(DFUOverSMPRestartAdvertisingHandler startAdvertisingCb);
	void ConfirmNewImage();
	void StartServer();
	void StartBLEAdvertising();
	bool IsEnabled() { return mIsEnabled; }

private:
	friend DFUOverSMP &GetDFUOverSMP(void);

	static int UploadConfirmHandler(uint32_t offset, uint32_t size, void *arg);
	static void OnBleDisconnect(bt_conn *conn, uint8_t reason);

	bool mIsEnabled;
	bt_conn_cb mBleConnCallbacks;
	DFUOverSMPRestartAdvertisingHandler restartAdvertisingCallback;

	static DFUOverSMP sDFUOverSMP;
};

inline DFUOverSMP &GetDFUOverSMP(void)
{
	return DFUOverSMP::sDFUOverSMP;
}
