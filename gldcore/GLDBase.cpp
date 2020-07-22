/*
 * GLDBase.cpp
 *
 *  Created on: Jul 16, 2020
 *      Author: 1scot
 */

#include "GLDBase.h"

char1024 GLDBase::GLDInBuf = '\0';
char1024 GLDBase::GLDOutBuf = '\0';

gld_string GLDBase::inBuffer;
gld_string GLDBase::outBuffer;

gld_string GLDBase::delim;
gld_string GLDBase::msgDelim;

/*GLDBase::~GLDBase(){
}*/


void GLDBase::addMsgOutBuf(gld_string &message){
	inBuffer = inBuffer + *msgDelim + message;
	GLDOutBuf = inBuffer.get_buffer_non_const();

}

void GLDBase::addDataOutBuf(OBJECT *obj, PROPERTYNAME name, char *value){
	gld_string *message = new gld_string(obj->name);
	*message = *message + delim + name + value;
	addMsgOutBuf(*message);
}



void GLDBase::netPktArrived(){
	gl_output("correct");
	while(!inBuffer.empty()){
		gld_string line = inBuffer.getStrUntilDelim(*msgDelim);

		char *from = inBuffer.getCharUntilDelim(*delim);
		double quantity = atof(inBuffer.getCharUntilDelim(*delim));
		double real_price = atof(inBuffer.getCharUntilDelim(*delim));
		KEY key = atoll(inBuffer.getCharUntilDelim(*delim));
		BIDDERSTATE state = charToState((inBuffer.getCharUntilDelim(*delim)));
		bool rebid = ('1' == *inBuffer.getCharUntilDelim(*delim));
		int64 mkt_id = atoll(inBuffer.getCharUntilDelim(*delim));
		submitImpl(from, quantity, real_price, key, state, rebid, mkt_id);
	}
}

int GLDBase::AM_submit(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id){
	if(false){
		return submitImpl(from, quantity, real_price, key, state, rebid, mkt_id);
	} else {
		return AM_submit_nolock(from, quantity, real_price, key, state, rebid, mkt_id);
	}
}

int GLDBase::AM_submit_nolock(char *from, double quantity, double real_price, KEY key, BIDDERSTATE state, bool rebid, int64 mkt_id){
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
}

EXPORT int network_set_value_by_name(OBJECT *obj, PROPERTYNAME name, char *value){
	if(false){
		*callback->properties.set_value_by_name;
	} else {//send over network
		FINDLIST *auction = gl_find_objects(FL_NEW,FT_CLASS,SAME,"auction",FT_END);
		OBJECT *objPtr = gl_find_next(auction,NULL);

		GLDBase *a = *objPtr;
		a->addDataOutBuf(obj, name, value);

		FUNCTIONADDR add;
		add = (FUNCTIONADDR)gl_get_function(objPtr, "addDataOutBuf");
		(void(*)(OBJECT *, PROPERTYNAME, char *))(*add);
	}
}


EXPORT int network_set_value_by_name(OBJECT *obj, PROPERTYNAME name, double value){
	if(false){//same implementation as gl_set_value_by_name in this case
		*callback->properties.set_value_by_name;
	} else {//send over network
		FINDLIST *auction = gl_find_objects(FL_NEW,FT_CLASS,SAME,"auction",FT_END);
		OBJECT *objPtr = gl_find_next(auction,NULL);

		GLDBase *a;
		//a->addDataOutBuf(obj, name, value);
	}
}

EXPORT void checkInBuf(){
	FINDLIST *auction = gl_find_objects(FL_NEW,FT_CLASS,SAME,"auction",FT_END);
	OBJECT *objPtr = gl_find_next(auction,NULL);

	GLDBase *a;
	while(!a->inBuffer.empty()){

		//if its bid, find the auction object and call netPktArrived
		//otherwise do gl_set_value_by_name (unless properties modified directly from omnet++)
	}
}


