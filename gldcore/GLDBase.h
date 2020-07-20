/*
 * GLDBase.h
 *
 *  Created on: Jul 16, 2020
 *      Author: 1scot
 */

#ifndef GLDCORE_GLDBASE_H_
#define GLDCORE_GLDBASE_H_

#include "gridlabd.h"

typedef int64 KEY;

typedef enum {
	BS_UNKNOWN=0,
	BS_OFF=1,
	BS_ON=2
} BIDDERSTATE;

BIDDERSTATE& charToState(char *s){
	BIDDERSTATE bidState;
	if(*s == '0'){
		bidState = BS_UNKNOWN;
	} else if(*s == '1'){
		bidState = BS_OFF;
	} else if(*s == '2'){
		bidState = BS_ON;
	} else {

	}
}

inline const char * const boolToString(bool b)
{
	return b ? "true" : "false";
}


class GLDBase {
	public:

		static gld_string GLDOutBuf;
		static gld_string GLDInBuf;

		static gld_string *delim = new gld_string("@%@");
		static gld_string *msgDelim = new gld_string("%@%");

		inline void addMsgOutBuf(gld_string &message){
			if(GLDOutBuf.empty()){
				GLDOutBuf = message;
			}
			GLDOutBuf = GLDOutBuf + msgDelim + message;
		};

	/*	 inline void addDataOutBuf(OBJECT *obj, PROPERTYNAME name, char *value){
			gld_string *message = new gld_string(obj->name);
			*message = *message + delim + name + value;
			addMsgOutBuf(*message);
		}*/

		template <typename T>
		inline void addDataOutBuf(OBJECT *obj, PROPERTYNAME name, T value){
			gld_string *message = new gld_string(obj->name);
			*message = *message + delim + name + value;
			addMsgOutBuf(*message);
		}

		virtual int submitImpl(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id) = 0;
		virtual int submit_nolockImpl(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id) = 0;

		inline void netPktArrived(){
			while(!GLDInBuf.empty()){
				gld_string line = GLDInBuf.getStrUntilDelim(*msgDelim);

				char *from = GLDInBuf.getCharUntilDelim(*delim);
				double quantity = atof(GLDInBuf.getCharUntilDelim(*delim));
				double real_price = atof(GLDInBuf.getCharUntilDelim(*delim));
				KEY key = atoll(GLDInBuf.getCharUntilDelim(*delim));
				BIDDERSTATE state = charToState((GLDInBuf.getCharUntilDelim(*delim)));
				bool rebid = ('1' == *GLDInBuf.getCharUntilDelim(*delim));
				int64 mkt_id = atoll(GLDInBuf.getCharUntilDelim(*delim));
				submitImpl(from, quantity, real_price, key, state, rebid, mkt_id);
			}
		};
		inline int AM_submit(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id){
			if(false){
				return submitImpl(from, quantity, real_price, key, state, rebid, mkt_id);
			} else {
				return AM_submit_nolock(from, quantity, real_price, key, state, rebid, mkt_id);
			}
		};

		inline int AM_submit_nolock(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id){
			if(true){
				double dblState = state;
				gld_string *message = new gld_string(from);
				*message = *message + delim + quantity + delim + real_price + delim + key +
						delim + dblState + delim + boolToString(rebid) + delim + mkt_id;
				addMsgOutBuf(*message);
				return 0;
			} else {
				submit_nolockImpl(from, quantity, real_price, key, state, rebid, mkt_id);
			}
		};
	};

	/** Set the value of a property in an object
		@see object_set_value_by_name()
	 **/
	inline int network_set_value_by_name(OBJECT *obj, PROPERTYNAME name, char *value){
		if(false){
			*callback->properties.set_value_by_name;
		} else {//send over network
			FINDLIST *auction = NULL;gl_find_objects(FL_NEW,FT_CLASS,SAME,"auction",FT_END);
			OBJECT *objPtr = gl_find_next(auction,NULL);

			GLDBase::addDataOutBuf(obj, name, value);
		}
	}

	/** Set the value of a property in an object
		@see object_set_value_by_name()
	 **/
	inline int network_set_value_by_name(OBJECT *obj, PROPERTYNAME name, double value){
	/*	if(false){
			*callback->properties.set_value_by_name;
		} else {//send over network
			GLDBase:addDataOutBuf(obj, name, value);
		}*/
	}

	inline void checkInBuf(){
		/*gld_string a(buf->GLDInBuf);
		while(!buf->GLDInBuf.empty()){
			//if its bid, find the auction object and call netPktArrived
			//otherwise do gl_set_value_by_name (unless properties modified directly from omnet++)
		}*/
	}
