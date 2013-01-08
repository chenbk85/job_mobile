//////////////////////////////////////////////////////////////////////
//
//  jcCommon Source Code
//
//  File: IStreamPersist.h
//  Description: IStreamPersist interface.
//
//  History:
//  - August 6, 2001: Created by Alberto Demichelis
//
//////////////////////////////////////////////////////////////////////

#ifndef GAME_ISTREAMPERSIST_H
#define GAME_ISTREAMPERSIST_H
#if _MSC_VER > 1000
# pragma once
#endif

namespace nMech
{
	namespace nLUA1
	{
		struct IScriptObject;
	}
}
class nMech::nJC_stream::CStream;

enum DirtyFlags 
{
		DIRTY_NAME		= 0x1,
		DIRTY_POS			= 0x2,
		DIRTY_ANGLES	= 0x4,
};

//!store the stream status per connection(per serverslot)
/*struct StreamStatus
{
	StreamStatus()
	{
		nUserFlags=0;
		nLastUpdate=0;
		nUpdateNumber=0;
	}
	unsigned int nUserFlags;
	unsigned int nLastUpdate;
	unsigned int nUpdateNumber;
};*/
///////////////////////////////////////////////
/*! This interface must be implemented by all objects that must be serialized
	through the network or file.
	
	REMARKS: The main pourpose of the serialization is reproduce the game remotely
		or saving and restoring.This mean that the object must not save everything
		but only what really need to be restored correctly.
*/
struct IStreamPersist
{
	/*!	serialize the object to a bitstream(network)
		@param stm the stream class that will store the bitstream
		@return true if succeded,false failed
		@see nMech::nJC_stream::CStream
	*/
	virtual bool Write(nMech::nJC_stream::CStream&) = 0;
	/*!	read the object from a stream(network)
		@param stm the stream class that store the bitstream
		@return true if succeded,false failed
		@see nMech::nJC_stream::CStream
	*/
	virtual bool Read(nMech::nJC_stream::CStream&) = 0;
	/*! check if the object must be syncronized since the last serialization
		@return true must be serialized, false the object didn't change
	*/
	virtual bool IsDirty() = 0;

	/*!	serialize the object to a bitstream(file persistence)
		@param stm the stream class that will store the bitstream
		@param pStream script wrapper for the stream(optional)
		@return true if succeded,false failed
		@see nMech::nJC_stream::CStream
	*/
	virtual bool Save(nMech::nJC_stream::CStream &stm) = 0;
	/*!	read the object from a stream(file persistence)
		@param stm the stream class that store the bitstream
		@param pStream script wrapper for the stream(optional)
		@return true if succeded,false failed
		@see nMech::nJC_stream::CStream
	*/
	virtual bool Load(nMech::nJC_stream::CStream &stm,nMech::nLUA1::IScriptObject *pStream=NULL) = 0;
};

#endif // GAME_ISTREAMPERSIST_H
