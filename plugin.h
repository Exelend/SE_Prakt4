/** 
 * File:   plugin.h
 * Author: Lehmann
 *
 * Inface definition for smart sensors.
 * 
 * Created on 10. November 2013, 15:49
 */

#ifndef PLUGIN_H
#define	PLUGIN_H

class Plugin {
public:
	Plugin(void);
	virtual ~Plugin(void);
    virtual void evalCycle(void) = 0;
    virtual bool result(void) = 0;
};

#endif	/* PLUGIN_H */

