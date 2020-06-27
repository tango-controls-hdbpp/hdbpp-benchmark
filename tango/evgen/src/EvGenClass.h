/*----- PROTECTED REGION ID(EvGenClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        EvGenClass.h
//
// description : Include for the EvGen root class.
//               This class is the singleton class for
//                the EvGen device class.
//               It contains all properties and methods which the 
//               EvGen requires only once e.g. the commands.
//
// project :     
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
//
// Elettra-Sincrotrone Trieste S.C.p.A. di interesse nazionale
// Strada Statale 14 - km 163,5 in AREA Science Park
// 34149 Basovizza, Trieste ITALY
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef EvGenClass_H
#define EvGenClass_H

#include <tango.h>
#include <EvGen.h>


/*----- PROTECTED REGION END -----*/	//	EvGenClass.h


namespace EvGen_ns
{
/*----- PROTECTED REGION ID(EvGenClass::classes for dynamic creation) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	EvGenClass::classes for dynamic creation

//=========================================
//	Define classes for attributes
//=========================================
//	Attribute scalar_double_ro class definition
class scalar_double_roAttrib: public Tango::Attr
{
public:
	scalar_double_roAttrib():Attr("scalar_double_ro",
			Tango::DEV_DOUBLE, Tango::READ) {};
	~scalar_double_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_scalar_double_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_scalar_double_ro_allowed(ty);}
};

//	Attribute scalar_double_rw class definition
class scalar_double_rwAttrib: public Tango::Attr
{
public:
	scalar_double_rwAttrib():Attr("scalar_double_rw",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~scalar_double_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_scalar_double_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_scalar_double_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_scalar_double_rw_allowed(ty);}
};

//	Attribute scalar_long_ro class definition
class scalar_long_roAttrib: public Tango::Attr
{
public:
	scalar_long_roAttrib():Attr("scalar_long_ro",
			Tango::DEV_LONG, Tango::READ) {};
	~scalar_long_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_scalar_long_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_scalar_long_ro_allowed(ty);}
};

//	Attribute scalar_long_rw class definition
class scalar_long_rwAttrib: public Tango::Attr
{
public:
	scalar_long_rwAttrib():Attr("scalar_long_rw",
			Tango::DEV_LONG, Tango::READ_WRITE) {};
	~scalar_long_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_scalar_long_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_scalar_long_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_scalar_long_rw_allowed(ty);}
};

//	Attribute scalar_bool_ro class definition
class scalar_bool_roAttrib: public Tango::Attr
{
public:
	scalar_bool_roAttrib():Attr("scalar_bool_ro",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~scalar_bool_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_scalar_bool_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_scalar_bool_ro_allowed(ty);}
};

//	Attribute scalar_bool_rw class definition
class scalar_bool_rwAttrib: public Tango::Attr
{
public:
	scalar_bool_rwAttrib():Attr("scalar_bool_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~scalar_bool_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_scalar_bool_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_scalar_bool_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_scalar_bool_rw_allowed(ty);}
};

//	Attribute scalar_ulong64_ro class definition
class scalar_ulong64_roAttrib: public Tango::Attr
{
public:
	scalar_ulong64_roAttrib():Attr("scalar_ulong64_ro",
			Tango::DEV_ULONG64, Tango::READ) {};
	~scalar_ulong64_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_scalar_ulong64_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_scalar_ulong64_ro_allowed(ty);}
};

//	Attribute scalar_ulong64_rw class definition
class scalar_ulong64_rwAttrib: public Tango::Attr
{
public:
	scalar_ulong64_rwAttrib():Attr("scalar_ulong64_rw",
			Tango::DEV_ULONG64, Tango::READ_WRITE) {};
	~scalar_ulong64_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_scalar_ulong64_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_scalar_ulong64_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_scalar_ulong64_rw_allowed(ty);}
};

//	Attribute enable_scalar_double_ro class definition
class enable_scalar_double_roAttrib: public Tango::Attr
{
public:
	enable_scalar_double_roAttrib():Attr("enable_scalar_double_ro",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_scalar_double_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_scalar_double_ro(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_scalar_double_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_scalar_double_ro_allowed(ty);}
};

//	Attribute enable_scalar_double_rw class definition
class enable_scalar_double_rwAttrib: public Tango::Attr
{
public:
	enable_scalar_double_rwAttrib():Attr("enable_scalar_double_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_scalar_double_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_scalar_double_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_scalar_double_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_scalar_double_rw_allowed(ty);}
};

//	Attribute enable_scalar_long_ro class definition
class enable_scalar_long_roAttrib: public Tango::Attr
{
public:
	enable_scalar_long_roAttrib():Attr("enable_scalar_long_ro",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_scalar_long_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_scalar_long_ro(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_scalar_long_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_scalar_long_ro_allowed(ty);}
};

//	Attribute enable_scalar_long_rw class definition
class enable_scalar_long_rwAttrib: public Tango::Attr
{
public:
	enable_scalar_long_rwAttrib():Attr("enable_scalar_long_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_scalar_long_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_scalar_long_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_scalar_long_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_scalar_long_rw_allowed(ty);}
};

//	Attribute enable_scalar_bool_ro class definition
class enable_scalar_bool_roAttrib: public Tango::Attr
{
public:
	enable_scalar_bool_roAttrib():Attr("enable_scalar_bool_ro",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_scalar_bool_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_scalar_bool_ro(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_scalar_bool_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_scalar_bool_ro_allowed(ty);}
};

//	Attribute enable_scalar_bool_rw class definition
class enable_scalar_bool_rwAttrib: public Tango::Attr
{
public:
	enable_scalar_bool_rwAttrib():Attr("enable_scalar_bool_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_scalar_bool_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_scalar_bool_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_scalar_bool_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_scalar_bool_rw_allowed(ty);}
};

//	Attribute enable_scalar_ulong64_ro class definition
class enable_scalar_ulong64_roAttrib: public Tango::Attr
{
public:
	enable_scalar_ulong64_roAttrib():Attr("enable_scalar_ulong64_ro",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_scalar_ulong64_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_scalar_ulong64_ro(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_scalar_ulong64_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_scalar_ulong64_ro_allowed(ty);}
};

//	Attribute enable_scalar_ulong64_rw class definition
class enable_scalar_ulong64_rwAttrib: public Tango::Attr
{
public:
	enable_scalar_ulong64_rwAttrib():Attr("enable_scalar_ulong64_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_scalar_ulong64_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_scalar_ulong64_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_scalar_ulong64_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_scalar_ulong64_rw_allowed(ty);}
};

//	Attribute enable_spectrum_double_ro class definition
class enable_spectrum_double_roAttrib: public Tango::Attr
{
public:
	enable_spectrum_double_roAttrib():Attr("enable_spectrum_double_ro",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_spectrum_double_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_spectrum_double_ro(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_spectrum_double_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_spectrum_double_ro_allowed(ty);}
};

//	Attribute enable_spectrum_double_rw class definition
class enable_spectrum_double_rwAttrib: public Tango::Attr
{
public:
	enable_spectrum_double_rwAttrib():Attr("enable_spectrum_double_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_spectrum_double_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_spectrum_double_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_spectrum_double_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_spectrum_double_rw_allowed(ty);}
};

//	Attribute enable_spectrum_long_ro class definition
class enable_spectrum_long_roAttrib: public Tango::Attr
{
public:
	enable_spectrum_long_roAttrib():Attr("enable_spectrum_long_ro",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_spectrum_long_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_spectrum_long_ro(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_spectrum_long_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_spectrum_long_ro_allowed(ty);}
};

//	Attribute enable_spectrum_long_rw class definition
class enable_spectrum_long_rwAttrib: public Tango::Attr
{
public:
	enable_spectrum_long_rwAttrib():Attr("enable_spectrum_long_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_spectrum_long_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_spectrum_long_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_spectrum_long_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_spectrum_long_rw_allowed(ty);}
};

//	Attribute enable_spectrum_bool_ro class definition
class enable_spectrum_bool_roAttrib: public Tango::Attr
{
public:
	enable_spectrum_bool_roAttrib():Attr("enable_spectrum_bool_ro",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_spectrum_bool_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_spectrum_bool_ro(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_spectrum_bool_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_spectrum_bool_ro_allowed(ty);}
};

//	Attribute enable_spectrum_bool_rw class definition
class enable_spectrum_bool_rwAttrib: public Tango::Attr
{
public:
	enable_spectrum_bool_rwAttrib():Attr("enable_spectrum_bool_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_spectrum_bool_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_spectrum_bool_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_spectrum_bool_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_spectrum_bool_rw_allowed(ty);}
};

//	Attribute enable_spectrum_ulong64_ro class definition
class enable_spectrum_ulong64_roAttrib: public Tango::Attr
{
public:
	enable_spectrum_ulong64_roAttrib():Attr("enable_spectrum_ulong64_ro",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_spectrum_ulong64_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_spectrum_ulong64_ro(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_spectrum_ulong64_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_spectrum_ulong64_ro_allowed(ty);}
};

//	Attribute enable_spectrum_ulong64_rw class definition
class enable_spectrum_ulong64_rwAttrib: public Tango::Attr
{
public:
	enable_spectrum_ulong64_rwAttrib():Attr("enable_spectrum_ulong64_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~enable_spectrum_ulong64_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_enable_spectrum_ulong64_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_enable_spectrum_ulong64_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_enable_spectrum_ulong64_rw_allowed(ty);}
};

//	Attribute spectrum_double_ro class definition
class spectrum_double_roAttrib: public Tango::SpectrumAttr
{
public:
	spectrum_double_roAttrib():SpectrumAttr("spectrum_double_ro",
			Tango::DEV_DOUBLE, Tango::READ, 10000) {};
	~spectrum_double_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_spectrum_double_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_spectrum_double_ro_allowed(ty);}
};

//	Attribute spectrum_double_rw class definition
class spectrum_double_rwAttrib: public Tango::SpectrumAttr
{
public:
	spectrum_double_rwAttrib():SpectrumAttr("spectrum_double_rw",
			Tango::DEV_DOUBLE, Tango::READ_WRITE, 10000) {};
	~spectrum_double_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_spectrum_double_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_spectrum_double_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_spectrum_double_rw_allowed(ty);}
};

//	Attribute spectrum_long_ro class definition
class spectrum_long_roAttrib: public Tango::SpectrumAttr
{
public:
	spectrum_long_roAttrib():SpectrumAttr("spectrum_long_ro",
			Tango::DEV_LONG, Tango::READ, 10000) {};
	~spectrum_long_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_spectrum_long_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_spectrum_long_ro_allowed(ty);}
};

//	Attribute spectrum_long_rw class definition
class spectrum_long_rwAttrib: public Tango::SpectrumAttr
{
public:
	spectrum_long_rwAttrib():SpectrumAttr("spectrum_long_rw",
			Tango::DEV_LONG, Tango::READ_WRITE, 10000) {};
	~spectrum_long_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_spectrum_long_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_spectrum_long_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_spectrum_long_rw_allowed(ty);}
};

//	Attribute spectrum_bool_ro class definition
class spectrum_bool_roAttrib: public Tango::SpectrumAttr
{
public:
	spectrum_bool_roAttrib():SpectrumAttr("spectrum_bool_ro",
			Tango::DEV_BOOLEAN, Tango::READ, 10000) {};
	~spectrum_bool_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_spectrum_bool_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_spectrum_bool_ro_allowed(ty);}
};

//	Attribute spectrum_bool_rw class definition
class spectrum_bool_rwAttrib: public Tango::SpectrumAttr
{
public:
	spectrum_bool_rwAttrib():SpectrumAttr("spectrum_bool_rw",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE, 10000) {};
	~spectrum_bool_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_spectrum_bool_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_spectrum_bool_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_spectrum_bool_rw_allowed(ty);}
};

//	Attribute spectrum_ulong64_ro class definition
class spectrum_ulong64_roAttrib: public Tango::SpectrumAttr
{
public:
	spectrum_ulong64_roAttrib():SpectrumAttr("spectrum_ulong64_ro",
			Tango::DEV_ULONG64, Tango::READ, 10000) {};
	~spectrum_ulong64_roAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_spectrum_ulong64_ro(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_spectrum_ulong64_ro_allowed(ty);}
};

//	Attribute spectrum_ulong64_rw class definition
class spectrum_ulong64_rwAttrib: public Tango::SpectrumAttr
{
public:
	spectrum_ulong64_rwAttrib():SpectrumAttr("spectrum_ulong64_rw",
			Tango::DEV_ULONG64, Tango::READ_WRITE, 10000) {};
	~spectrum_ulong64_rwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<EvGen *>(dev))->read_spectrum_ulong64_rw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<EvGen *>(dev))->write_spectrum_ulong64_rw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<EvGen *>(dev))->is_spectrum_ulong64_rw_allowed(ty);}
};


//=========================================
//	Define classes for commands
//=========================================
//	Command Start class definition
class StartClass : public Tango::Command
{
public:
	StartClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	StartClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~StartClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<EvGen *>(dev))->is_Start_allowed(any);}
};

//	Command Stop class definition
class StopClass : public Tango::Command
{
public:
	StopClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	StopClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~StopClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<EvGen *>(dev))->is_Stop_allowed(any);}
};


/**
 *	The EvGenClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  EvGenClass : public Tango::DeviceClass
#else
class EvGenClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(EvGenClass::Additionnal DServer data members) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	EvGenClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static EvGenClass *init(const char *);
		static EvGenClass *instance();
		~EvGenClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		EvGenClass(string &);
		static EvGenClass *_instance;
		void command_factory();
		void attribute_factory(vector<Tango::Attr *> &);
		void pipe_factory();
		void write_class_property();
		void set_default_property();
		void get_class_property();
		string get_cvstag();
		string get_cvsroot();
	
	private:
		void device_factory(const Tango::DevVarStringArray *);
		void create_static_attribute_list(vector<Tango::Attr *> &);
		void erase_dynamic_attributes(const Tango::DevVarStringArray *,vector<Tango::Attr *> &);
		vector<string>	defaultAttList;
		Tango::Attr *get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname);
};

}	//	End of namespace

#endif   //	EvGen_H
