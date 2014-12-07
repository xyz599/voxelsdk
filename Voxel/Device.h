/*
 * TI Voxel Lib component.
 *
 * Copyright (c) 2014 Texas Instruments Inc.
 */

#ifndef VOXEL_DEVICE_H
#define VOXEL_DEVICE_H

#include "Common.h"
#include <sstream>

namespace Voxel
{
  
class Device
{
public:
  enum Interface {
    USB = 0,
    LPT = 1,
    SERIAL = 2,
    I2C = 3
  };
protected:
  String _id; // in the format interface::device::serialnumber. "device" for USB devices is "vendorid:productid"
  Interface _interfaceID;
  String _deviceID;
  String _serialNumber;
public:
  Device(Interface interfaceid, const String &deviceid, const String &serialnumber): _interfaceID(interfaceid), 
  _deviceID(deviceid), _serialNumber(serialnumber) 
  { 
    std::ostringstream s;
    s << _interfaceID << "::" <<  _deviceID << "::" << _serialNumber;
    _id = s.str();
  }
  
  inline const String &id() const { return _id; }
  
  inline Interface interface() const { return _interfaceID; }
  inline const String &deviceID() const { return _deviceID; }
  inline const String &serialNumber() const { return _serialNumber; }
};

typedef Ptr<Device> DevicePtr;

class USBDevice: public Device
{
  uint16_t _vendorID, _productID; 
public:
  USBDevice(uint16_t vendorid, uint16_t productid, const String &serialnumber): 
    Device(Device::USB, getHex(vendorid) + ":" + getHex(productid), serialnumber), _vendorID(vendorid), _productID(productid) {}
  
  inline uint16_t vendorID() const { return _vendorID; }
  inline uint16_t productID() const { return _productID; }
};

class DeviceScanner
{
protected:
  virtual Vector<DevicePtr> _scan() = 0;
public:
  static Vector<DevicePtr> scan();
};

class USBDeviceScanner: public DeviceScanner
{
protected:
  virtual Vector<DevicePtr> _scan();
  friend class DeviceScanner;
};

}

#endif // DEVICE_H
