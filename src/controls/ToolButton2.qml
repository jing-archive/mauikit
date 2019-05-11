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

import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Controls.impl 2.3
import QtQuick.Layouts 1.3

import org.kde.kirigami 2.4 as Kirigami
import "private"

ToolButton
{
	id: control
	focusPolicy: Qt.NoFocus
	/* Controlc color scheming */
	ColorScheme 
	{
		id: colorScheme
		backgroundColor: "transparent"
		borderColor: "transparent"
	}
	property alias colorScheme : colorScheme
	/***************************/
	
// 	property alias backgroundRec: _background
	
	property bool isMask:  true
	property string iconName: ""
	property string iconFallback: ""
	property int size: iconSize
	property color iconColor: colorScheme.textColor
	property bool anim: false
	property string tooltipText : ""
	property bool showIndicator: false
	
	hoverEnabled: !isMobile
	
	implicitWidth: control.visible ? Math.max(background ? background.implicitWidth : 0,
							contentItem.implicitWidth + leftPadding + rightPadding) : 0
	implicitHeight: control.visible ? Math.max(background ? background.implicitHeight : 0,
							 contentItem.implicitHeight + topPadding + bottomPadding) : 0
	
	height: control.visible ? (control.display === ToolButton.IconOnly ? size + space.medium : implicitHeight) : 0
	width: control.visible ? (control.display === ToolButton.IconOnly ? height : implicitWidth + space.small) : 0
	
	icon.name:  control.iconName
	icon.source: control.iconFallback
	icon.width:  control.size
	icon.height: control.size
	icon.color: !control.isMask ? "transparent" :  (down || pressed || checked) ? colorScheme.highlightColor : iconColor
	
	onClicked: if(anim) animIcon.running = true
	
	flat: true
	highlighted: !isMask
	font.pointSize: control.display === ToolButton.TextUnderIcon ? fontSizes.small : undefined
	
	display: control.text.length > 0 ? (isWide ? ToolButton.TextBesideIcon : ToolButton.TextUnderIcon) : ToolButton.IconOnly
	spacing: space.tiny
	
	
	
	background: Rectangle
	{
		id: _background
		implicitHeight: control.visible ? iconSizes.medium : 0
		implicitWidth: control.visible ? iconSizes.medium : 0
		
		anchors.centerIn: control.icon
		color: /*(down || pressed || checked) */ checked && enabled  ?
		Qt.lighter(colorScheme.highlightColor, 1.2) : colorScheme.backgroundColor
		radius: unit * 3
		opacity: (down || pressed || checked) && enabled  ?  0.5 : 1
		border.color: colorScheme.borderColor
		
		
	}
	
	Rectangle
	{
		id: _indicator
		visible: control.visible
		color: control.colorScheme.highlightColor
		height: unit * 5
		width: control.width - space.small
		
		anchors.bottom: parent.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		visible: control.showIndicator
	}
	
	contentItem: IconLabel
	{
		id: _iconLabel
		visible: control.visible
		spacing:  control.display === ToolButton.TextUnderIcon ? space.tiny : control.spacing
		mirrored: control.mirrored
		display: control.display
		icon: control.icon
		text: control.text
		font: control.font
		color: control.iconColor
	}
	
	
// 			background: Rectangle
// 			{
// 				implicitHeight: control.visible? control.height : 0
// 				implicitWidth: control.visible? control.width : 0
// 				
// 				anchors.centerIn: control
// 				color: /*(down || pressed || checked) */ checked && enabled  ?
// 				Qt.lighter(colorScheme.highlightColor, 1.2) : colorScheme.backgroundColor
// 				radius: unit * 3
// 				opacity: (down || pressed || checked) && enabled  ?  0.5 : 1
// 				border.color: colorScheme.borderColor
// 			}
// 			
// 			contentItem: GridLayout
// 			{
// 				id: _contentLayout
// 				anchors.fill: control
// 				
// 				columns: (control.display === ToolButton.TextUnderIcon) || (control.display === ToolButton.IconOnly)? 1 : 2
// 				rows: (control.display === ToolButton.TextUnderIcon) ? 2 : 1
// 				
// 				columnSpacing: 0
// 				rowSpacing: 0
// 				
// 				Item
// 				{
// 					Layout.fillWidth: true
// 					Layout.fillHeight: true
// 					Layout.row: 1
// 					Layout.column: 1
// 					Layout.alignment: Qt.AlignBottom
// 					
// 					Kirigami.Icon
// 					{
// 						anchors.centerIn: parent
// 						source: control.iconName
// 						isMask: control.isMask	
// 						height: size
// 						width: height
// 						color: isMask ? control.iconColor : "transparent"
// 					}
// 				}
// 				
// 				Item
// 				{
// 					visible: control.text.length && control.text
// 					Layout.fillWidth: true
// 					Layout.fillHeight: true
// 					Layout.row: (control.display === ToolButton.TextUnderIcon) ? 2 : 1
// 					Layout.column: (control.display === ToolButton.TextUnderIcon) || (control.display === ToolButton.IconOnly)? 1 : 2
// 					Layout.alignment: Qt.AlignTop
// 					
// 					Label
// 					{
// 						anchors.fill: parent
// 						font: control.font
// 						text: control.text
// 						color: control.iconColor
// 						horizontalAlignment: Qt.AlignHCenter
// 						verticalAlignment: Qt.AlignVCenter
// 					}
// 				}
// 			}
	
	SequentialAnimation
	{
		id: animIcon
		PropertyAnimation
		{
			target: control
			property: "icon.color"
			easing.type: Easing.InOutQuad
			from: colorScheme.highlightColor
			to: iconColor
			duration: 500
		}
	}
	
	ToolTip.delay: 1000
	ToolTip.timeout: 5000
	ToolTip.visible: hovered && !isMobile && tooltipText.length > 0
	ToolTip.text: tooltipText
}
