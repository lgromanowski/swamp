/** \file server_listeners.h */
#ifndef SWAMP_SERVER_LISTENERS_H
#define SWAMP_SERVER_LISTENERS_H

/**\addtogroup server */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp {


struct Connection;

/**
 * \struct AcceptListener
 * \ingroup Server
 */
struct AcceptListener {
	virtual ~AcceptListener(){}
	virtual bool notify(Connection*) = 0;
};

/**
 * \struct ReadRequestListener
 * \ingroup Server
 */
struct ReadRequestListener {
	virtual ~ReadRequestListener(){}
	virtual bool notify(Connection*) = 0;
};

} /* namespace swamp */

#endif /* SWAMP_SERVER_LISTENERS_H */
