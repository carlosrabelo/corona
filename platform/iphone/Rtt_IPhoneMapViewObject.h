//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Corona Labs Inc.
// Contact: support@coronalabs.com
//
// This file is part of the Corona game engine.
//
// Commercial License Usage
// Licensees holding valid commercial Corona licenses may use this file in
// accordance with the commercial license agreement between you and 
// Corona Labs Inc. For licensing terms and conditions please contact
// support@coronalabs.com or visit https://coronalabs.com/com-license
//
// GNU General Public License Usage
// Alternatively, this file may be used under the terms of the GNU General
// Public license version 3. The license is as published by the Free Software
// Foundation and appearing in the file LICENSE.GPL3 included in the packaging
// of this file. Please review the following information to ensure the GNU 
// General Public License requirements will
// be met: https://www.gnu.org/licenses/gpl-3.0.html
//
// For overview and more information on licensing please refer to README.md
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _Rtt_IPhoneMapViewObject_H__
#define _Rtt_IPhoneMapViewObject_H__

#include "Rtt_IPhoneDisplayObject.h"

#include <math.h>
#import <MapKit/MapKit.h>
#import <MapKit/MKAnnotation.h>


// ----------------------------------------------------------------------------

@class Rtt_MKMapView;

namespace Rtt
{

// ----------------------------------------------------------------------------

class IPhoneMapViewObject : public IPhoneDisplayObject
{
	public:
		typedef IPhoneMapViewObject Self;
		typedef IPhoneDisplayObject Super;

	public:
		IPhoneMapViewObject( const Rect& bounds );
		virtual ~IPhoneMapViewObject();

	public:
		// PlatformDisplayObject
		virtual bool Initialize();

		// DisplayObject
		virtual const LuaProxyVTable& ProxyVTable() const;
		
	public:
		static int getUserLocation( lua_State *L );
		static int setRegion( lua_State *L );
		static int setCenter( lua_State *L );
		static int requestLocation( lua_State *L ); // New. Asynchronous.
		static int getAddressLocation( lua_State *L ); // Old. Synchronous.
		static int addMarker( lua_State *L );
		static int removeMarker( lua_State *L );
		static int removeAllMarkers( lua_State *L );
		static int nearestAddress( lua_State *L );


	protected:
		// static int setTextColor( lua_State *L );
        int markerIdCounter;

	public:
		// MLuaTableBridge
		virtual int ValueForKey( lua_State *L, const char key[] ) const;
		virtual bool SetValueForKey( lua_State *L, const char key[], int valueIndex );
};

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------

@interface Rtt_MKMapView : MKMapView <CLLocationManagerDelegate>
{
	Rtt::IPhoneMapViewObject *owner;
}

@property(nonatomic, assign) BOOL trackUserLocationAfterAuthorization;
@property(nonatomic, assign) Rtt::IPhoneMapViewObject *owner;

@end

@interface AddressAnnotationWithCallout : NSObject<MKAnnotation> {
	CLLocationCoordinate2D coordinate;
	
	NSString *mTitle;
	NSString *mSubTitle;
}

@property(nonatomic, retain) MKAnnotationView* annotationView;
@property int annotationId;
@property(nonatomic, assign) Rtt::LuaResource* luaResourceForListener;

@end


// ----------------------------------------------------------------------------

#endif // _Rtt_IPhoneMapViewObject_H__
