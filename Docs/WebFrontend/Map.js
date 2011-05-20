/*
 *  Open Source Routing Machine (OSRM) - Web (GUI) Interface
 *	Copyright (C) Pascal Neis, 2011
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU AFFERO General Public License as published by
 *	the Free Software Foundation; either version 3 of the License, or
 *	any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU Affero General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *	or see http://www.gnu.org/licenses/agpl.txt.
 */
 
/**
 * Title: Map.js
 * Description: JS file to show a map, for markers, left slide div, ...
 *
 * @author Pascal Neis, pascal@neis-one.org 
 * @version 0.1 2011-05-15
 */

//======================
// OBJECTS
//Map
var map;

//Status object for what position actually a coordinate is searched
var status = ''; //possible values [start,end]
function getStatus(){ return status; }
function setStatus(stat){ status = stat; }

//Layer
var dragLayer;
var vectorLayerRoute;
var markersLayer;

//======================
// FUNCTIONS
/*
 * init()-Function to create the map div
 */
function init(){
	//Create Map
	map = new OpenLayers.Map ("map", {
		controls:[
			new OpenLayers.Control.Navigation(),
			new OpenLayers.Control.Permalink(),
			new OpenLayers.Control.LayerSwitcher()],
		maxExtent: new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34),
		maxResolution: 156543.0399,
		numZoomLevels: 19,
		units: 'm',
		projection: new OpenLayers.Projection("EPSG:900913"),
		displayProjection: new OpenLayers.Projection("EPSG:4326")
	} );
	//Add the base layers.
	
	var coverageLayer = new OpenLayers.Layer.Vector("Coverage", {
        style: {
                    strokeColor: "#000000",
                    strokeTransparency: 0.5,
                    strokeWidth: 4
        }
    });
	if("map.project-osrm.org" == location.host) {
	    var coveragePointList = [
	        new OpenLayers.Geometry.Point(-11.99, 58.80),
	        new OpenLayers.Geometry.Point(-11.99, 35.30),
	        new OpenLayers.Geometry.Point(-7.57, 35.30),
	        new OpenLayers.Geometry.Point(9.22, 38.24),
	        new OpenLayers.Geometry.Point(15.38, 35.39),
	        new OpenLayers.Geometry.Point(18.92, 40.02),
	        new OpenLayers.Geometry.Point(15.70, 42.25),
	        new OpenLayers.Geometry.Point(15.70, 55.40),
	        new OpenLayers.Geometry.Point(30.31, 60.29),
	        new OpenLayers.Geometry.Point(30.31, 71.27),
	        new OpenLayers.Geometry.Point(21.01, 71.27),
	        new OpenLayers.Geometry.Point(-11.99, 58.80)
	    ];
	
	    var line_string = new OpenLayers.Geometry.LineString(coveragePointList).transform(new OpenLayers.Projection("EPSG:4326"), new OpenLayers.Projection("EPSG:900913"));
	    coverageLayer.addFeatures([new OpenLayers.Feature.Vector(line_string)]);
	
	    map.addLayer(coverageLayer);
	}
	
	map.addLayer(new OpenLayers.Layer.OSM.Mapnik("Mapnik"));
	map.addLayer(new OpenLayers.Layer.OSM.MapQuest("MapQuest"));
	map.addLayer(new OpenLayers.Layer.OSM.Osmarender("Osmarender"));
	//Add layer for the route
	vectorLayerRoute = new OpenLayers.Layer.Vector("Route",{maxResolution: 156543.0339});
	map.addLayer(vectorLayerRoute);
	
	//Add Layerswitcher
	map.addControl(new OpenLayers.Control.LayerSwitcher());

	//Add Panzoombar
	var panZoomBar = new OpenLayers.Control.PanZoomBar({id:'panzoombar',displayClass:'olControlPanZoomBar'})
	map.addControl(panZoomBar);	
	//Customize the position of the panzoombar
	document.getElementById('panzoombar').style.left="400px";
	document.getElementById('panzoombar').style.top="25px";

	//Create drag vector layer
	dragLayer = new OpenLayers.Layer.Vector(
                "Start/End Marker",{
                    styleMap: new OpenLayers.StyleMap({
                        // Set the external graphic and background graphic images.
                        externalGraphic: '${icon}',
                        // Makes sure the background graphic is placed correctly relative
                        // to the external graphic.
                        backgroundXOffset: 0,
                        backgroundYOffset: -7,
                        
                        // Set the z-indexes of both graphics to make sure the background
                        // graphics stay in the background (shadows on top of markers looks
                        // odd; let's not do that).
                        graphicZIndex: 10,
                        backgroundGraphicZIndex: 11,

                        pointRadius: 10,
                        graphicWidth: 22,
                        graphicHeight: 34
                    }),
                    rendererOptions: {yOrdering: true}
                }
           );
    // Add a drag feature control to move features around.
    var dragFeatures = new OpenLayers.Control.DragFeature(dragLayer,
		{ onDrag: function(feature, pixel){
			feature.move(map.getLonLatFromPixel(pixel));
			if(!ISCALCULATING){ routing(true); }},
		  onComplete: function(feature, pixel){
			feature.move(map.getLonLatFromPixel(pixel));
			routing(false); },
		  onLeave: function(f){
			alert("here");
			if(!ISCALCULATING){ routing(false); }}
		});
    map.addControl(dragFeatures);
    dragFeatures.activate();
	map.addLayers([dragLayer]);

	//Add a marker layer
	markersLayer = new OpenLayers.Layer.Markers("Markers");
    map.addLayer(markersLayer);
    
	//Add zoom event for rerouting
	map.events.on({zoomend: function(e) {reroute();}});
	
	// Set center of the map
	if (!map.getCenter()){
		map.setCenter(new OpenLayers.LonLat(600000, 6600000),6);
	}
}

//Helper Functions
function checkReturn(textfieldname,e){
	var evt = e || window.event;
	if(!evt){ return; }
		
	var key = 0;
	if (evt.keyCode) { key = evt.keyCode; } 
	else if (typeof(evt.which)!= 'undefined') { key = evt.which; } 
	if( key == 13 && textfieldname=='start'){ setStatus('start'); geocodeAddress('start'); return; }
	if( key == 13 && textfieldname=='end'){ setStatus('end'); geocodeAddress('end'); return; }
}

function closeOpenDiv(name){ 
	if(document.getElementById(name).style.display == 'none'){ document.getElementById(name).style.display = ''; }
	else{ document.getElementById(name).style.display = 'none'; }
}