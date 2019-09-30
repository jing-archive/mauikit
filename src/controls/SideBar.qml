/*
 *   Copyright 2018 Camilo Higuita <milo.h@aol.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import org.kde.mauikit 1.0 as Maui
import "private"

Maui.AbstractSideBar
{
    id: control

    //     ApplicationWindow.height -ApplicationWindow.header.height - ApplicationWindow.footer.height
    implicitWidth: privateProperties.isCollapsed && collapsed && collapsible  ? collapsedSize : preferredWidth
    width: implicitWidth
    modal: false
    interactive: Kirigami.Settings.isMobile && modal && !collapsible && !collapsed

    default property alias content : _content.data
    property alias model : _listBrowser.model
    property alias count : _listBrowser.count
    
    property alias section : _listBrowser.section
    property alias currentIndex: _listBrowser.currentIndex

    property int iconSize : Maui.Style.iconSizes.small
    property bool showLabels: control.width > collapsedSize

  

    property QtObject privateProperties : QtObject
    {
        property bool isCollapsed: control.collapsed
    }

    signal itemClicked(int index)
    signal itemRightClicked(int index)
	onModalChanged: visible = true
	visible: true	
	
    onCollapsedChanged :
    {
        if(!collapsible)
            return

        if(!collapsed && modal)
        {
            modal = false

        }

        if(!modal && !collapsed)
        {
            privateProperties.isCollapsed = false
        }

        if(collapsed && !modal)
        {
            privateProperties.isCollapsed = true
        }
    }


    Item
    {
        id: _content
        anchors.fill: parent
        anchors.topMargin: Maui.Style.space.tiny
        anchors.bottomMargin: Maui.Style.space.tiny
        anchors.margins: Maui.Style.unit
        
        data: Maui.ListBrowser
        {
            id: _listBrowser
            anchors.fill: parent
            listView.flickableDirection: Flickable.VerticalFlick
            Rectangle
            {
                anchors.fill: parent
                z: -1
                color: Kirigami.Theme.backgroundColor
            }

            delegate: Maui.ListDelegate
            {
                id: itemDelegate
                iconSize: control.iconSize
                labelVisible: control.showLabels

                leftPadding:  Maui.Style.space.tiny
                rightPadding:  Maui.Style.space.tiny

                Connections
                {
                    target: itemDelegate
                    onClicked:
                    {
                        control.currentIndex = index
                        control.itemClicked(index)
                    }

                    onRightClicked:
                    {
                        control.currentIndex = index
                        control.itemRightClicked(index)
                    }

                    onPressAndHold:
                    {
                        control.currentIndex = index
                        control.itemRightClicked(index)
                    }
                }
            }
        }
    }

    MouseArea
    {
		id: _mouseArea
		anchors.fill: parent
		hoverEnabled: Kirigami.Settings.isMobile ? false : true
		propagateComposedEvents: true
		enabled: control.collapsible
		visible: enabled
		parent: control.contentItem
		property int startY
		property int startX
		
		onEntered:
		{
			if(Kirigami.Settings.isMobile)
				return;
			
			if(containsMouse && privateProperties.isCollapsed && control.collapsed && control.collapsible && !control.modal)
			{
				expand()
			}
		}
		
		onExited:
		{
			if(Kirigami.Settings.isMobile)
				return
				
				if(!privateProperties.isCollapsed  && control.collapsible && control.collapsed && control.modal)
				{
					collapse()
				}
		}
		
		onPositionChanged:
		{
			if (!pressed)
				return
				
				if(mouse.y !== startY && mouse.x < (startX + Maui.Style.space.big))
				{
					if(!_listBrowser.listView.atYEnd || !_listBrowser.listView.atYBegin)
						_listBrowser.listView.flick(0,(mouse.y -startY) * 2 )
				}
				
				if(!control.collapsible)
					return
					
					if(control.collapsible && control.collapsed && Kirigami.Settings.isMobile)
					{
						if(mouse.x > (control.collapsedSize*2))
						{
							expand()
							
						}else if((mouse.x*2) < control.collapsedSize)
						{
							collapse()
						}
					}
		}
		
		onPressed:
		{
			startY = mouse.y
			startX = mouse.x
			console.log("PRESSED SIDEBAR", !(Kirigami.Settings.isMobile && !modal && !collapsed && !privateProperties.isCollapsed))
			console.log(Kirigami.Settings.isMobile , modal , collapsed , privateProperties.isCollapsed)
			mouse.accepted = !(!modal && !collapsed && !privateProperties.isCollapsed) && Kirigami.Settings.isMobile
		}
		
		onReleased:
		{
			mouse.accepted = true
			
			if(!control.collapsible)
				return
				
				if(control.collapsible && control.collapsed && Kirigami.Settings.isMobile)
				{
					if(mouse.x > (control.collapsedSize*2))
					{
						expand()
						
					}else
					{
						collapse()
					}
				}
				
		}
	}
	
	function collapse()
	{
		if(collapsible && !privateProperties.isCollapsed)
		{
			modal = false
			privateProperties.isCollapsed  = true
		}
	}
	
	function expand()
	{
		if(collapsible && privateProperties.isCollapsed)
		{
			modal = true
			privateProperties.isCollapsed = false
		}
	}
}

