#include "NvsManager.h"
#include "Arduino.h"

#if defined(__AVR__)
#include <avr/eeprom.h>
int NvsManager::nextFreeAdress = 0;
///< returns an adress and reserves the requested number of bytes. the "key" is currently only used on ESP32 platforms, and ignored everywhere else
NvsAddress NvsManager::getAddressFor(ARDUPAR_CONST_CHAR *key, size_t bytes)
{
	int curAdress = nextFreeAdress;
	nextFreeAdress += bytes;
	NvsAddress retVal;
	retVal.addressOffset = curAdress;
	return (retVal);
}

///< read raw data from permanent storage
bool NvsManager::read_bytes(void *data, NvsAddress address, int nBytes)
{
	eeprom_read_block(data, (void *)address.addressOffset, nBytes);
	return true; // TODO: implement checksum check here
}
///< write raw data to permanent storage
bool NvsManager::write_bytes(void *data, NvsAddress address, int nBytes)
{
	eeprom_write_block(data, (void *)address.addressOffset, nBytes);
	return true;
}
#endif

#ifdef __XTENSA__
#include <rom/crc.h>
bool NvsManager::isInitialized = false;
Preferences NvsManager::preferences;

NvsAddress NvsManager::getAddressFor(ARDUPAR_CONST_CHAR *key, size_t bytes)
{
	// due to key length restrictions in the Preferences/NVS library, we use a hash of the key internally.
	// if you happen to be unlucky and have a collision, change one of the addresses
	int len=strlen(key);
	int32_t crc= crc32_le(0, (const u_int8_t*)key ,  len);
		NvsAddress retVal;
	sprintf(retVal.crcOfKeyAsHex,  "%08X",crc);

	retVal.key = key;
	return (retVal);
}

///< read raw data from permanent storage
bool NvsManager::read_bytes(void *data, NvsAddress address, int nBytes)
{
	if (!NvsManager::isInitialized)
	{
		NvsManager::preferences.begin("ardupar");
		NvsManager::isInitialized = true;
	}
	TRACE(F("reading "));
	TRACE(nBytes);
	TRACE(F(" bytes from key:"));

	TRACE(address.crcOfKeyAsHex);

	bool success = preferences.getBytes((const char *)address.crcOfKeyAsHex, data, nBytes) != 0;
	TRACE(F(" success? "));
	TRACELN(success);
	return success;
}
///< write raw data to permanent storage
bool NvsManager::write_bytes(void *data, NvsAddress address, int nBytes)
{
	if (!NvsManager::isInitialized)
	{
		NvsManager::preferences.begin("ardupar");
		NvsManager::isInitialized = true;
	}
	TRACE(F("writing "));
	TRACE(nBytes);
	TRACE(F(" bytes to key:"));

	TRACE(address.crcOfKeyAsHex);
	bool success = preferences.putBytes((const char *)address.crcOfKeyAsHex, data, nBytes) != 0;
	TRACE(F(" success? "));
	TRACELN(success);
	return success;
}
#endif
