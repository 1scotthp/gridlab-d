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

		//virtual ~GLDBase();
		static char1024 GLDOutBuf;
		static char1024 GLDInBuf;

		static gld_string inBuffer;
		static gld_string outBuffer;

		static gld_string *delim;
		static gld_string *msgDelim;

		void addMsgOutBuf(gld_string &message);
		void addDataOutBuf(OBJECT *obj, PROPERTYNAME name, char *value);

		virtual int submitImpl(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id) = 0;
		virtual int submit_nolockImpl(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id) = 0;

		void netPktArrived();

		int AM_submit(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id);

		int AM_submit_nolock(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id);
};


	/** Set the value of a property in an object
		@see object_set_value_by_name()
	 **/
	int network_set_value_by_name(OBJECT *obj, PROPERTYNAME name, char *value);


	/** Set the value of a property in an object
		@see object_set_value_by_name()
	 **/
	int network_set_value_by_name(OBJECT *obj, PROPERTYNAME name, double value){
	/*	if(false){
			*callback->properties.set_value_by_name;
		} else {//send over network
			GLDBase:addDataOutBuf(obj, name, value);
		}*/
	}

	void checkInBuf(){
		/*gld_string a(buf->GLDInBuf);
		while(!buf->GLDInBuf.empty()){
			//if its bid, find the auction object and call netPktArrived
			//otherwise do gl_set_value_by_name (unless properties modified directly from omnet++)
		}*/
	}

#endif
