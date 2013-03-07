<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="5" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="7" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="no" active="no"/>
<layer number="201" name="201bmp" color="2" fill="1" visible="no" active="no"/>
<layer number="202" name="202bmp" color="3" fill="1" visible="no" active="no"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="con-lstb">
<description>&lt;b&gt;Pin Headers&lt;/b&gt;&lt;p&gt;
Naming:&lt;p&gt;
MA = male&lt;p&gt;
# contacts - # rows&lt;p&gt;
W = angled&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MA12-2">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-14.605" y1="2.54" x2="-13.335" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="2.54" x2="-12.7" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="1.905" x2="-12.065" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="2.54" x2="-10.795" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="2.54" x2="-10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="2.54" x2="-15.24" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-13.335" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-10.795" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="-2.54" x2="-12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="-2.54" x2="-12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="1.905" x2="-15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="-1.905" x2="-14.605" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="-2.54" x2="-14.605" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-2.54" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-2.54" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.54" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="6.985" y1="2.54" x2="7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="8.255" y1="2.54" x2="9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="2.54" x2="10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="10.795" y2="2.54" width="0.1524" layer="21"/>
<wire x1="10.795" y1="2.54" x2="12.065" y2="2.54" width="0.1524" layer="21"/>
<wire x1="12.065" y1="2.54" x2="12.7" y2="1.905" width="0.1524" layer="21"/>
<wire x1="8.255" y1="2.54" x2="7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="12.7" y1="1.905" x2="13.335" y2="2.54" width="0.1524" layer="21"/>
<wire x1="13.335" y1="2.54" x2="14.605" y2="2.54" width="0.1524" layer="21"/>
<wire x1="14.605" y1="2.54" x2="15.24" y2="1.905" width="0.1524" layer="21"/>
<wire x1="15.24" y1="1.905" x2="15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="6.985" y1="-2.54" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-2.54" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="12.7" y1="-1.905" x2="12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="12.065" y1="-2.54" x2="10.795" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.795" y1="-2.54" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-2.54" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="15.24" y1="-1.905" x2="14.605" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="14.605" y1="-2.54" x2="13.335" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="13.335" y1="-2.54" x2="12.7" y2="-1.905" width="0.1524" layer="21"/>
<pad name="1" x="-13.97" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-11.43" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="-8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="-6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="-3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-13.97" y="1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-11.43" y="1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="-8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="-6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="-3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="17" x="6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="19" x="8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="21" x="11.43" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="23" x="13.97" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="16" x="3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="18" x="6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="20" x="8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="22" x="11.43" y="1.27" drill="1.016" shape="octagon"/>
<pad name="24" x="13.97" y="1.27" drill="1.016" shape="octagon"/>
<text x="-14.351" y="-4.191" size="1.27" layer="21" ratio="10">1</text>
<text x="-15.24" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="12.7" y="2.921" size="1.27" layer="21" ratio="10">24</text>
<text x="2.54" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-11.684" y1="-1.524" x2="-11.176" y2="-1.016" layer="51"/>
<rectangle x1="-14.224" y1="-1.524" x2="-13.716" y2="-1.016" layer="51"/>
<rectangle x1="-9.144" y1="-1.524" x2="-8.636" y2="-1.016" layer="51"/>
<rectangle x1="-4.064" y1="-1.524" x2="-3.556" y2="-1.016" layer="51"/>
<rectangle x1="-6.604" y1="-1.524" x2="-6.096" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="-1.524" x2="4.064" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="6.096" y1="-1.524" x2="6.604" y2="-1.016" layer="51"/>
<rectangle x1="11.176" y1="-1.524" x2="11.684" y2="-1.016" layer="51"/>
<rectangle x1="8.636" y1="-1.524" x2="9.144" y2="-1.016" layer="51"/>
<rectangle x1="13.716" y1="-1.524" x2="14.224" y2="-1.016" layer="51"/>
<rectangle x1="-14.224" y1="1.016" x2="-13.716" y2="1.524" layer="51"/>
<rectangle x1="-11.684" y1="1.016" x2="-11.176" y2="1.524" layer="51"/>
<rectangle x1="-9.144" y1="1.016" x2="-8.636" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="1.016" x2="-6.096" y2="1.524" layer="51"/>
<rectangle x1="-4.064" y1="1.016" x2="-3.556" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="3.556" y1="1.016" x2="4.064" y2="1.524" layer="51"/>
<rectangle x1="6.096" y1="1.016" x2="6.604" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="1.016" x2="9.144" y2="1.524" layer="51"/>
<rectangle x1="11.176" y1="1.016" x2="11.684" y2="1.524" layer="51"/>
<rectangle x1="13.716" y1="1.016" x2="14.224" y2="1.524" layer="51"/>
</package>
<package name="MA08-2">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-9.525" y1="2.54" x2="-8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-2.54" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-2.54" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="6.985" y1="2.54" x2="7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="8.255" y1="2.54" x2="9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="2.54" x2="10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-2.54" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="8.255" y1="-2.54" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="6.985" y1="-2.54" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="-8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="-3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="-3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="16" x="8.89" y="1.27" drill="1.016" shape="octagon"/>
<text x="-9.398" y="-4.191" size="1.27" layer="21" ratio="10">1</text>
<text x="-10.16" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="7.62" y="2.921" size="1.27" layer="21" ratio="10">16</text>
<text x="0" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-6.604" y1="-1.524" x2="-6.096" y2="-1.016" layer="51"/>
<rectangle x1="-9.144" y1="-1.524" x2="-8.636" y2="-1.016" layer="51"/>
<rectangle x1="-4.064" y1="-1.524" x2="-3.556" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="-1.524" x2="4.064" y2="-1.016" layer="51"/>
<rectangle x1="-9.144" y1="1.016" x2="-8.636" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="1.016" x2="-6.096" y2="1.524" layer="51"/>
<rectangle x1="-4.064" y1="1.016" x2="-3.556" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="3.556" y1="1.016" x2="4.064" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="-1.524" x2="9.144" y2="-1.016" layer="51"/>
<rectangle x1="6.096" y1="-1.524" x2="6.604" y2="-1.016" layer="51"/>
<rectangle x1="6.096" y1="1.016" x2="6.604" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="1.016" x2="9.144" y2="1.524" layer="51"/>
</package>
<package name="MA03-1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-3.175" y1="1.27" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-3.81" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-0.635" size="1.27" layer="21" ratio="10">1</text>
<text x="-3.81" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="-2.794" y1="-0.254" x2="-2.286" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
</package>
<package name="MA04-1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-5.08" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.223" y="-0.635" size="1.27" layer="21" ratio="10">1</text>
<text x="0.635" y="1.651" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="5.334" y="-0.635" size="1.27" layer="21" ratio="10">4</text>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MA12-2">
<wire x1="3.81" y1="-15.24" x2="-3.81" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="2.54" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-10.16" x2="2.54" y2="-10.16" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-12.7" x2="2.54" y2="-12.7" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-7.62" x2="-1.27" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-10.16" x2="-1.27" y2="-10.16" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-12.7" x2="-1.27" y2="-12.7" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-1.27" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-1.27" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-1.27" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-1.27" y2="2.54" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="10.16" x2="2.54" y2="10.16" width="0.6096" layer="94"/>
<wire x1="1.27" y1="7.62" x2="2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="10.16" x2="-1.27" y2="10.16" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="7.62" x2="-1.27" y2="7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="15.24" x2="2.54" y2="15.24" width="0.6096" layer="94"/>
<wire x1="1.27" y1="12.7" x2="2.54" y2="12.7" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="15.24" x2="-1.27" y2="15.24" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="12.7" x2="-1.27" y2="12.7" width="0.6096" layer="94"/>
<wire x1="-3.81" y1="17.78" x2="-3.81" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-15.24" x2="3.81" y2="17.78" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="17.78" x2="3.81" y2="17.78" width="0.4064" layer="94"/>
<text x="-3.81" y="-17.78" size="1.778" layer="96">&gt;VALUE</text>
<text x="-3.81" y="18.542" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-12.7" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="-10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="-7.62" y="-12.7" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="4" x="-7.62" y="-10.16" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="6" x="-7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="7" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="9" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="-7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="10" x="-7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="11" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="13" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="15" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="12" x="-7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="14" x="-7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="16" x="-7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="17" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="19" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="18" x="-7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="20" x="-7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="21" x="7.62" y="12.7" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="23" x="7.62" y="15.24" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="22" x="-7.62" y="12.7" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="24" x="-7.62" y="15.24" visible="pad" length="middle" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="MA08-2">
<wire x1="3.81" y1="-10.16" x2="-3.81" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="2.54" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-1.27" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-1.27" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-7.62" x2="-1.27" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-1.27" y2="2.54" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="10.16" x2="2.54" y2="10.16" width="0.6096" layer="94"/>
<wire x1="1.27" y1="7.62" x2="2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="10.16" x2="-1.27" y2="10.16" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="7.62" x2="-1.27" y2="7.62" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-1.27" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-3.81" y1="12.7" x2="-3.81" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-10.16" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="12.7" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<text x="-3.81" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<text x="-3.81" y="13.462" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="-7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="4" x="-7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="6" x="-7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="7" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="9" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="-7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="10" x="-7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="11" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="13" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="15" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="12" x="-7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="14" x="-7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="16" x="-7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="MA03-1">
<wire x1="3.81" y1="-5.08" x2="-1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="-1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<text x="-1.27" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="5.842" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
<symbol name="MA04-1">
<wire x1="3.81" y1="-7.62" x2="-1.27" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="-1.27" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-7.62" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<text x="-1.27" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="5.842" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MA12-2" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="MA12-2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA12-2">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="10" pad="10"/>
<connect gate="1" pin="11" pad="11"/>
<connect gate="1" pin="12" pad="12"/>
<connect gate="1" pin="13" pad="13"/>
<connect gate="1" pin="14" pad="14"/>
<connect gate="1" pin="15" pad="15"/>
<connect gate="1" pin="16" pad="16"/>
<connect gate="1" pin="17" pad="17"/>
<connect gate="1" pin="18" pad="18"/>
<connect gate="1" pin="19" pad="19"/>
<connect gate="1" pin="2" pad="2"/>
<connect gate="1" pin="20" pad="20"/>
<connect gate="1" pin="21" pad="21"/>
<connect gate="1" pin="22" pad="22"/>
<connect gate="1" pin="23" pad="23"/>
<connect gate="1" pin="24" pad="24"/>
<connect gate="1" pin="3" pad="3"/>
<connect gate="1" pin="4" pad="4"/>
<connect gate="1" pin="5" pad="5"/>
<connect gate="1" pin="6" pad="6"/>
<connect gate="1" pin="7" pad="7"/>
<connect gate="1" pin="8" pad="8"/>
<connect gate="1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MA08-2" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MA08-2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA08-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MA03-1" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MA03-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA03-1">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MA04-1" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="MA04-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA04-1">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="2" pad="2"/>
<connect gate="1" pin="3" pad="3"/>
<connect gate="1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Freedom">
<description>Library for the Freescale Freedom FRDM-KL25Z Board</description>
<packages>
<package name="FRDM-KL25Z">
<description>Use straight headers (2 6-pin and 2 8-pin) to connect to an Arduino</description>
<wire x1="-23.495" y1="-21.59" x2="-22.225" y2="-21.59" width="0.127" layer="21"/>
<wire x1="-23.495" y1="-21.59" x2="-24.13" y2="-20.955" width="0.127" layer="21"/>
<wire x1="-22.225" y1="-21.59" x2="-21.59" y2="-20.955" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-20.955" x2="-24.13" y2="-19.685" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-19.685" x2="-23.495" y2="-19.05" width="0.127" layer="21"/>
<wire x1="-23.495" y1="-19.05" x2="-24.13" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-18.415" x2="-24.13" y2="-17.145" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-17.145" x2="-23.495" y2="-16.51" width="0.127" layer="21"/>
<wire x1="-23.495" y1="-16.51" x2="-24.13" y2="-15.875" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-15.875" x2="-24.13" y2="-14.605" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-14.605" x2="-23.495" y2="-13.97" width="0.127" layer="21"/>
<wire x1="-23.495" y1="-13.97" x2="-24.13" y2="-13.335" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-13.335" x2="-24.13" y2="-12.065" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-12.065" x2="-23.495" y2="-11.43" width="0.127" layer="21"/>
<wire x1="-23.495" y1="-11.43" x2="-24.13" y2="-10.795" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-10.795" x2="-24.13" y2="-9.525" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-9.525" x2="-23.495" y2="-8.89" width="0.127" layer="21"/>
<wire x1="-23.495" y1="-8.89" x2="-24.13" y2="-8.255" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-8.255" x2="-24.13" y2="-6.985" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-6.985" x2="-23.495" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-23.495" y1="-6.35" x2="-22.225" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-3.81" x2="-19.05" y2="-3.175" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-3.175" x2="-19.05" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-1.905" x2="-19.685" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-1.27" x2="-19.05" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-0.635" x2="-19.05" y2="0.635" width="0.127" layer="21"/>
<wire x1="-19.05" y1="0.635" x2="-19.685" y2="1.27" width="0.127" layer="21"/>
<wire x1="-19.685" y1="1.27" x2="-19.05" y2="1.905" width="0.127" layer="21"/>
<wire x1="-19.05" y1="1.905" x2="-19.05" y2="3.175" width="0.127" layer="21"/>
<wire x1="-19.05" y1="3.175" x2="-19.685" y2="3.81" width="0.127" layer="21"/>
<wire x1="-19.685" y1="3.81" x2="-19.05" y2="4.445" width="0.127" layer="21"/>
<wire x1="-19.05" y1="5.715" x2="-19.685" y2="6.35" width="0.127" layer="21"/>
<wire x1="-19.685" y1="6.35" x2="-19.05" y2="6.985" width="0.127" layer="21"/>
<wire x1="-19.05" y1="6.985" x2="-19.05" y2="8.255" width="0.127" layer="21"/>
<wire x1="-19.05" y1="8.255" x2="-19.685" y2="8.89" width="0.127" layer="21"/>
<wire x1="-19.685" y1="8.89" x2="-19.05" y2="9.525" width="0.127" layer="21"/>
<wire x1="-19.05" y1="15.875" x2="-19.685" y2="16.51" width="0.127" layer="21"/>
<wire x1="-23.495" y1="16.51" x2="-24.13" y2="15.875" width="0.127" layer="21"/>
<wire x1="-24.13" y1="9.525" x2="-23.495" y2="8.89" width="0.127" layer="21"/>
<wire x1="-23.495" y1="8.89" x2="-24.13" y2="8.255" width="0.127" layer="21"/>
<wire x1="-24.13" y1="8.255" x2="-24.13" y2="6.985" width="0.127" layer="21"/>
<wire x1="-24.13" y1="6.985" x2="-23.495" y2="6.35" width="0.127" layer="21"/>
<wire x1="-23.495" y1="6.35" x2="-24.13" y2="5.715" width="0.127" layer="21"/>
<wire x1="-24.13" y1="5.715" x2="-24.13" y2="4.445" width="0.127" layer="21"/>
<wire x1="-24.13" y1="4.445" x2="-23.495" y2="3.81" width="0.127" layer="21"/>
<wire x1="-23.495" y1="3.81" x2="-24.13" y2="3.175" width="0.127" layer="21"/>
<wire x1="-24.13" y1="3.175" x2="-24.13" y2="1.905" width="0.127" layer="21"/>
<wire x1="-24.13" y1="1.905" x2="-23.495" y2="1.27" width="0.127" layer="21"/>
<wire x1="-23.495" y1="1.27" x2="-24.13" y2="0.635" width="0.127" layer="21"/>
<wire x1="-24.13" y1="0.635" x2="-24.13" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-0.635" x2="-23.495" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-23.495" y1="-1.27" x2="-24.13" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-1.905" x2="-24.13" y2="-3.175" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-3.175" x2="-23.495" y2="-3.81" width="0.127" layer="21"/>
<wire x1="24.765" y1="-21.59" x2="26.035" y2="-21.59" width="0.127" layer="21"/>
<wire x1="26.035" y1="-21.59" x2="26.67" y2="-20.955" width="0.127" layer="21"/>
<wire x1="26.67" y1="-20.955" x2="26.67" y2="-19.685" width="0.127" layer="21"/>
<wire x1="26.67" y1="-19.685" x2="26.035" y2="-19.05" width="0.127" layer="21"/>
<wire x1="26.035" y1="-19.05" x2="26.67" y2="-18.415" width="0.127" layer="21"/>
<wire x1="26.67" y1="-18.415" x2="26.67" y2="-17.145" width="0.127" layer="21"/>
<wire x1="26.67" y1="-17.145" x2="26.035" y2="-16.51" width="0.127" layer="21"/>
<wire x1="26.035" y1="-16.51" x2="26.67" y2="-15.875" width="0.127" layer="21"/>
<wire x1="26.67" y1="-15.875" x2="26.67" y2="-14.605" width="0.127" layer="21"/>
<wire x1="26.67" y1="-14.605" x2="26.035" y2="-13.97" width="0.127" layer="21"/>
<wire x1="26.035" y1="-13.97" x2="26.67" y2="-13.335" width="0.127" layer="21"/>
<wire x1="26.67" y1="-13.335" x2="26.67" y2="-12.065" width="0.127" layer="21"/>
<wire x1="26.67" y1="-12.065" x2="26.035" y2="-11.43" width="0.127" layer="21"/>
<wire x1="26.035" y1="-11.43" x2="26.67" y2="-10.795" width="0.127" layer="21"/>
<wire x1="26.67" y1="-10.795" x2="26.67" y2="-9.525" width="0.127" layer="21"/>
<wire x1="26.67" y1="-9.525" x2="26.035" y2="-8.89" width="0.127" layer="21"/>
<wire x1="26.035" y1="-8.89" x2="26.67" y2="-8.255" width="0.127" layer="21"/>
<wire x1="26.67" y1="-8.255" x2="26.67" y2="-6.985" width="0.127" layer="21"/>
<wire x1="26.67" y1="-6.985" x2="26.035" y2="-6.35" width="0.127" layer="21"/>
<wire x1="26.035" y1="-6.35" x2="26.67" y2="-5.715" width="0.127" layer="21"/>
<wire x1="26.67" y1="-5.715" x2="26.67" y2="-4.445" width="0.127" layer="21"/>
<wire x1="26.67" y1="-4.445" x2="26.035" y2="-3.81" width="0.127" layer="21"/>
<wire x1="26.035" y1="-3.81" x2="26.67" y2="-3.175" width="0.127" layer="21"/>
<wire x1="26.67" y1="-1.905" x2="26.035" y2="-1.27" width="0.127" layer="21"/>
<wire x1="26.035" y1="-1.27" x2="24.765" y2="-1.27" width="0.127" layer="21"/>
<wire x1="24.765" y1="-1.27" x2="24.13" y2="-1.905" width="0.127" layer="21"/>
<wire x1="24.13" y1="-20.955" x2="24.765" y2="-21.59" width="0.127" layer="21"/>
<wire x1="26.035" y1="0" x2="26.67" y2="0.635" width="0.127" layer="21"/>
<wire x1="26.67" y1="0.635" x2="26.67" y2="1.905" width="0.127" layer="21"/>
<wire x1="26.67" y1="1.905" x2="26.035" y2="2.54" width="0.127" layer="21"/>
<wire x1="26.035" y1="2.54" x2="26.67" y2="3.175" width="0.127" layer="21"/>
<wire x1="26.67" y1="3.175" x2="26.67" y2="4.445" width="0.127" layer="21"/>
<wire x1="26.67" y1="4.445" x2="26.035" y2="5.08" width="0.127" layer="21"/>
<wire x1="26.035" y1="5.08" x2="26.67" y2="5.715" width="0.127" layer="21"/>
<wire x1="26.67" y1="5.715" x2="26.67" y2="6.985" width="0.127" layer="21"/>
<wire x1="26.67" y1="6.985" x2="26.035" y2="7.62" width="0.127" layer="21"/>
<wire x1="26.035" y1="7.62" x2="26.67" y2="8.255" width="0.127" layer="21"/>
<wire x1="26.67" y1="8.255" x2="26.67" y2="9.525" width="0.127" layer="21"/>
<wire x1="26.67" y1="9.525" x2="26.035" y2="10.16" width="0.127" layer="21"/>
<wire x1="26.035" y1="10.16" x2="26.67" y2="10.795" width="0.127" layer="21"/>
<wire x1="26.67" y1="10.795" x2="26.67" y2="12.065" width="0.127" layer="21"/>
<wire x1="26.67" y1="12.065" x2="26.035" y2="12.7" width="0.127" layer="21"/>
<wire x1="26.035" y1="12.7" x2="26.67" y2="13.335" width="0.127" layer="21"/>
<wire x1="26.67" y1="13.335" x2="26.67" y2="14.605" width="0.127" layer="21"/>
<wire x1="26.67" y1="14.605" x2="26.035" y2="15.24" width="0.127" layer="21"/>
<wire x1="26.035" y1="15.24" x2="26.67" y2="15.875" width="0.127" layer="21"/>
<wire x1="26.67" y1="15.875" x2="26.67" y2="17.145" width="0.127" layer="21"/>
<wire x1="26.67" y1="17.145" x2="26.035" y2="17.78" width="0.127" layer="21"/>
<wire x1="26.035" y1="17.78" x2="26.67" y2="18.415" width="0.127" layer="21"/>
<wire x1="26.67" y1="24.765" x2="26.035" y2="25.4" width="0.127" layer="21"/>
<wire x1="22.225" y1="25.4" x2="21.59" y2="24.765" width="0.127" layer="21"/>
<wire x1="21.59" y1="18.415" x2="22.225" y2="17.78" width="0.127" layer="21"/>
<wire x1="22.225" y1="17.78" x2="21.59" y2="17.145" width="0.127" layer="21"/>
<wire x1="21.59" y1="17.145" x2="21.59" y2="15.875" width="0.127" layer="21"/>
<wire x1="21.59" y1="15.875" x2="22.225" y2="15.24" width="0.127" layer="21"/>
<wire x1="22.225" y1="15.24" x2="21.59" y2="14.605" width="0.127" layer="21"/>
<wire x1="21.59" y1="14.605" x2="21.59" y2="13.335" width="0.127" layer="21"/>
<wire x1="21.59" y1="13.335" x2="22.225" y2="12.7" width="0.127" layer="21"/>
<wire x1="22.225" y1="12.7" x2="21.59" y2="12.065" width="0.127" layer="21"/>
<wire x1="21.59" y1="12.065" x2="21.59" y2="10.795" width="0.127" layer="21"/>
<wire x1="21.59" y1="10.795" x2="22.225" y2="10.16" width="0.127" layer="21"/>
<wire x1="22.225" y1="10.16" x2="21.59" y2="9.525" width="0.127" layer="21"/>
<wire x1="21.59" y1="9.525" x2="21.59" y2="8.255" width="0.127" layer="21"/>
<wire x1="21.59" y1="8.255" x2="22.225" y2="7.62" width="0.127" layer="21"/>
<wire x1="22.225" y1="7.62" x2="21.59" y2="6.985" width="0.127" layer="21"/>
<wire x1="21.59" y1="6.985" x2="21.59" y2="5.715" width="0.127" layer="21"/>
<wire x1="21.59" y1="5.715" x2="22.225" y2="5.08" width="0.127" layer="21"/>
<wire x1="22.225" y1="5.08" x2="21.59" y2="4.445" width="0.127" layer="21"/>
<wire x1="21.59" y1="4.445" x2="21.59" y2="3.175" width="0.127" layer="21"/>
<wire x1="21.59" y1="3.175" x2="22.225" y2="2.54" width="0.127" layer="21"/>
<wire x1="22.225" y1="2.54" x2="21.59" y2="1.905" width="0.127" layer="21"/>
<wire x1="21.59" y1="1.905" x2="21.59" y2="0.635" width="0.127" layer="21"/>
<wire x1="21.59" y1="0.635" x2="22.225" y2="0" width="0.127" layer="21"/>
<text x="-24.765" y="1.905" size="0.6096" layer="21" rot="R90">GND</text>
<text x="-24.765" y="-0.635" size="0.6096" layer="21" rot="R90">GND</text>
<text x="-24.765" y="-3.175" size="0.6096" layer="21" rot="R90">VIN</text>
<text x="-24.765" y="4.445" size="0.6096" layer="21" rot="R90">5V</text>
<text x="-24.765" y="6.985" size="0.6096" layer="21" rot="R90">3V3</text>
<text x="-24.765" y="9.525" size="0.6096" layer="21" rot="R90">RES</text>
<text x="-24.765" y="-8.255" size="1.016" layer="21" rot="R90">A0</text>
<text x="-24.765" y="-10.795" size="1.016" layer="21" rot="R90">A1</text>
<text x="-24.765" y="-13.335" size="1.016" layer="21" rot="R90">A2</text>
<text x="-24.765" y="-15.875" size="1.016" layer="21" rot="R90">A3</text>
<text x="-24.765" y="-18.415" size="1.016" layer="21" rot="R90">A4</text>
<text x="-24.765" y="-20.955" size="1.016" layer="21" rot="R90">A5</text>
<text x="27.305" y="-20.955" size="1.27" layer="21">2</text>
<text x="27.305" y="-18.415" size="1.27" layer="21">4</text>
<text x="27.305" y="-15.875" size="1.27" layer="21">6</text>
<text x="27.305" y="-13.335" size="1.27" layer="21">8</text>
<text x="27.305" y="-10.795" size="1.27" layer="21">10</text>
<text x="27.305" y="-8.255" size="1.27" layer="21">12</text>
<text x="27.305" y="-5.715" size="1.27" layer="21">14</text>
<text x="27.305" y="-3.175" size="1.27" layer="21">16</text>
<text x="27.305" y="0.635" size="1.27" layer="21">8</text>
<text x="27.305" y="3.175" size="1.27" layer="21">9</text>
<text x="27.305" y="5.715" size="1.27" layer="21">10</text>
<text x="27.305" y="8.255" size="1.27" layer="21">11</text>
<text x="27.305" y="10.795" size="1.27" layer="21">12</text>
<text x="27.305" y="13.335" size="1.27" layer="21">13</text>
<text x="21.59" y="-23.495" size="1.27" layer="21">&gt;VALUE</text>
<text x="30.48" y="5.715" size="1.27" layer="21">PWM</text>
<text x="30.48" y="8.255" size="1.27" layer="21">PWM</text>
<text x="27.305" y="15.875" size="1.27" layer="21">GND</text>
<text x="26.67" y="18.415" size="1.27" layer="21">AREF</text>
<wire x1="22.225" y1="-21.59" x2="23.495" y2="-21.59" width="0.127" layer="21"/>
<wire x1="23.495" y1="-21.59" x2="24.13" y2="-20.955" width="0.127" layer="21"/>
<wire x1="26.67" y1="-3.175" x2="26.67" y2="-1.905" width="0.127" layer="21"/>
<wire x1="24.13" y1="-1.905" x2="23.495" y2="-1.27" width="0.127" layer="21"/>
<wire x1="23.495" y1="-1.27" x2="22.225" y2="-1.27" width="0.127" layer="21"/>
<wire x1="22.225" y1="-1.27" x2="21.59" y2="-1.905" width="0.127" layer="21"/>
<wire x1="21.59" y1="-1.905" x2="21.59" y2="-3.175" width="0.127" layer="21"/>
<wire x1="21.59" y1="-3.175" x2="22.225" y2="-3.81" width="0.127" layer="21"/>
<wire x1="22.225" y1="-3.81" x2="21.59" y2="-4.445" width="0.127" layer="21"/>
<wire x1="21.59" y1="-4.445" x2="21.59" y2="-5.715" width="0.127" layer="21"/>
<wire x1="21.59" y1="-5.715" x2="22.225" y2="-6.35" width="0.127" layer="21"/>
<wire x1="22.225" y1="-6.35" x2="21.59" y2="-6.985" width="0.127" layer="21"/>
<wire x1="21.59" y1="-6.985" x2="21.59" y2="-8.255" width="0.127" layer="21"/>
<wire x1="21.59" y1="-8.255" x2="22.225" y2="-8.89" width="0.127" layer="21"/>
<wire x1="22.225" y1="-8.89" x2="21.59" y2="-9.525" width="0.127" layer="21"/>
<wire x1="21.59" y1="-9.525" x2="21.59" y2="-10.795" width="0.127" layer="21"/>
<wire x1="21.59" y1="-10.795" x2="22.225" y2="-11.43" width="0.127" layer="21"/>
<wire x1="22.225" y1="-11.43" x2="21.59" y2="-12.065" width="0.127" layer="21"/>
<wire x1="21.59" y1="-12.065" x2="21.59" y2="-13.335" width="0.127" layer="21"/>
<wire x1="21.59" y1="-13.335" x2="22.225" y2="-13.97" width="0.127" layer="21"/>
<wire x1="22.225" y1="-13.97" x2="21.59" y2="-14.605" width="0.127" layer="21"/>
<wire x1="21.59" y1="-14.605" x2="21.59" y2="-15.875" width="0.127" layer="21"/>
<wire x1="21.59" y1="-15.875" x2="22.225" y2="-16.51" width="0.127" layer="21"/>
<wire x1="22.225" y1="-16.51" x2="21.59" y2="-17.145" width="0.127" layer="21"/>
<wire x1="21.59" y1="-17.145" x2="21.59" y2="-18.415" width="0.127" layer="21"/>
<wire x1="21.59" y1="-18.415" x2="22.225" y2="-19.05" width="0.127" layer="21"/>
<wire x1="22.225" y1="-19.05" x2="21.59" y2="-19.685" width="0.127" layer="21"/>
<wire x1="21.59" y1="-19.685" x2="21.59" y2="-20.955" width="0.127" layer="21"/>
<wire x1="21.59" y1="-20.955" x2="22.225" y2="-21.59" width="0.127" layer="21"/>
<text x="19.685" y="-20.955" size="1.27" layer="21">1</text>
<text x="19.685" y="-18.415" size="1.27" layer="21">3</text>
<text x="19.685" y="-15.875" size="1.27" layer="21">5</text>
<text x="19.685" y="-13.335" size="1.27" layer="21">7</text>
<text x="19.685" y="-10.795" size="1.27" layer="21">9</text>
<text x="18.415" y="-8.255" size="1.27" layer="21">11</text>
<text x="18.415" y="-5.715" size="1.27" layer="21">13</text>
<text x="18.415" y="-3.175" size="1.27" layer="21">15</text>
<pad name="PTC11" x="22.86" y="-2.54" drill="0.8" shape="square"/>
<pad name="PTC10" x="22.86" y="-5.08" drill="0.8" shape="square"/>
<pad name="PTC6" x="22.86" y="-7.62" drill="0.8" shape="square"/>
<pad name="PTC5" x="22.86" y="-10.16" drill="0.8" shape="square"/>
<pad name="PTC4" x="22.86" y="-12.7" drill="0.8" shape="square"/>
<pad name="PTC3" x="22.86" y="-15.24" drill="0.8" shape="square"/>
<pad name="PTC0" x="22.86" y="-17.78" drill="0.8" shape="square"/>
<pad name="PTC7" x="22.86" y="-20.32" drill="0.8" shape="square"/>
<pad name="A0" x="-22.86" y="-7.62" drill="0.8" shape="square"/>
<pad name="A1" x="-22.86" y="-10.16" drill="0.8" shape="square"/>
<pad name="A2" x="-22.86" y="-12.7" drill="0.8" shape="square"/>
<pad name="A3" x="-22.86" y="-15.24" drill="0.8" shape="square"/>
<pad name="A4" x="-22.86" y="-17.78" drill="0.8" shape="square"/>
<pad name="A5" x="-22.86" y="-20.32" drill="0.8" shape="square"/>
<pad name="D7" x="25.4" y="-2.54" drill="0.8" shape="square"/>
<pad name="D6" x="25.4" y="-5.08" drill="0.8" shape="square"/>
<pad name="D5" x="25.4" y="-7.62" drill="0.8" shape="square"/>
<pad name="D4" x="25.4" y="-10.16" drill="0.8" shape="square"/>
<pad name="D3" x="25.4" y="-12.7" drill="0.8" shape="square"/>
<pad name="D2" x="25.4" y="-15.24" drill="0.8" shape="square"/>
<pad name="D1" x="25.4" y="-17.78" drill="0.8" shape="square"/>
<pad name="D0" x="25.4" y="-20.32" drill="0.8" shape="square"/>
<pad name="PTE20" x="-20.32" y="-7.62" drill="0.8" shape="square"/>
<wire x1="-20.955" y1="-21.59" x2="-19.685" y2="-21.59" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-21.59" x2="-19.05" y2="-20.955" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-20.955" x2="-19.05" y2="-19.685" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-19.685" x2="-19.685" y2="-19.05" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-19.05" x2="-19.05" y2="-18.415" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-18.415" x2="-19.05" y2="-17.145" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-17.145" x2="-19.685" y2="-16.51" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-16.51" x2="-19.05" y2="-15.875" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-15.875" x2="-19.05" y2="-14.605" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-14.605" x2="-19.685" y2="-13.97" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-13.97" x2="-19.05" y2="-13.335" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-13.335" x2="-19.05" y2="-12.065" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-12.065" x2="-19.685" y2="-11.43" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-11.43" x2="-19.05" y2="-10.795" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-10.795" x2="-19.05" y2="-9.525" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-9.525" x2="-19.685" y2="-8.89" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-8.89" x2="-19.05" y2="-8.255" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-8.255" x2="-19.05" y2="-6.985" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-6.985" x2="-19.685" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-6.35" x2="-20.955" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-21.59" y1="-20.955" x2="-20.955" y2="-21.59" width="0.127" layer="21"/>
<wire x1="-21.59" y1="-6.985" x2="-22.225" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-20.955" y1="-6.35" x2="-21.59" y2="-6.985" width="0.127" layer="21"/>
<pad name="PTE21" x="-20.32" y="-10.16" drill="0.8" shape="square"/>
<pad name="PTE22" x="-20.32" y="-12.7" drill="0.8" shape="square"/>
<pad name="PTE23" x="-20.32" y="-15.24" drill="0.8" shape="square"/>
<pad name="PTE29" x="-20.32" y="-17.78" drill="0.8" shape="square"/>
<pad name="PTE30" x="-20.32" y="-20.32" drill="0.8" shape="square"/>
<pad name="RESET" x="-22.86" y="10.16" drill="0.8" shape="square"/>
<pad name="P3V3" x="-22.86" y="7.62" drill="0.8" shape="square"/>
<pad name="5V" x="-22.86" y="5.08" drill="0.8" shape="square"/>
<pad name="GND1" x="-22.86" y="2.54" drill="0.8" shape="square"/>
<pad name="GND0" x="-22.86" y="0" drill="0.8" shape="square"/>
<pad name="VIN" x="-22.86" y="-2.54" drill="0.8" shape="square"/>
<wire x1="-22.225" y1="16.51" x2="-23.495" y2="16.51" width="0.127" layer="21"/>
<wire x1="-19.685" y1="16.51" x2="-20.955" y2="16.51" width="0.127" layer="21"/>
<wire x1="-22.225" y1="-3.81" x2="-23.495" y2="-3.81" width="0.127" layer="21"/>
<wire x1="-19.685" y1="-3.81" x2="-20.955" y2="-3.81" width="0.127" layer="21"/>
<wire x1="-20.955" y1="16.51" x2="-21.59" y2="15.875" width="0.127" layer="21"/>
<wire x1="-21.59" y1="15.875" x2="-22.225" y2="16.51" width="0.127" layer="21"/>
<wire x1="-21.59" y1="-3.175" x2="-20.955" y2="-3.81" width="0.127" layer="21"/>
<wire x1="-22.225" y1="-3.81" x2="-21.59" y2="-3.175" width="0.127" layer="21"/>
<pad name="3V3" x="-22.86" y="12.7" drill="0.8" shape="square"/>
<pad name="PTB9" x="-20.32" y="12.7" drill="0.8" shape="square"/>
<pad name="PTB10" x="-20.32" y="10.16" drill="0.8" shape="square"/>
<pad name="PTB11" x="-20.32" y="7.62" drill="0.8" shape="square"/>
<pad name="PTE2" x="-20.32" y="5.08" drill="0.8" shape="square"/>
<pad name="PTE3" x="-20.32" y="2.54" drill="0.8" shape="square"/>
<pad name="PTE4" x="-20.32" y="0" drill="0.8" shape="square"/>
<pad name="PTE5" x="-20.32" y="-2.54" drill="0.8" shape="square"/>
<pad name="NC" x="-22.86" y="15.24" drill="0.8" shape="square"/>
<pad name="PTB8" x="-20.32" y="15.24" drill="0.8" shape="square"/>
<wire x1="-24.13" y1="14.605" x2="-23.495" y2="13.97" width="0.127" layer="21"/>
<wire x1="-23.495" y1="13.97" x2="-24.13" y2="13.335" width="0.127" layer="21"/>
<wire x1="-24.13" y1="15.875" x2="-24.13" y2="14.605" width="0.127" layer="21"/>
<wire x1="-19.05" y1="15.875" x2="-19.05" y2="14.605" width="0.127" layer="21"/>
<wire x1="-24.13" y1="13.335" x2="-24.13" y2="12.065" width="0.127" layer="21"/>
<wire x1="-19.05" y1="12.065" x2="-19.05" y2="13.335" width="0.127" layer="21"/>
<wire x1="-19.685" y1="13.97" x2="-19.05" y2="14.605" width="0.127" layer="21"/>
<wire x1="-23.495" y1="11.43" x2="-24.13" y2="10.795" width="0.127" layer="21"/>
<wire x1="-19.05" y1="9.525" x2="-19.05" y2="10.795" width="0.127" layer="21"/>
<wire x1="-19.05" y1="10.795" x2="-19.685" y2="11.43" width="0.127" layer="21"/>
<wire x1="-19.685" y1="11.43" x2="-19.05" y2="12.065" width="0.127" layer="21"/>
<wire x1="-19.05" y1="13.335" x2="-19.685" y2="13.97" width="0.127" layer="21"/>
<wire x1="-24.13" y1="12.065" x2="-23.495" y2="11.43" width="0.127" layer="21"/>
<wire x1="-24.13" y1="9.525" x2="-24.13" y2="10.795" width="0.127" layer="21"/>
<text x="-24.765" y="12.065" size="0.6096" layer="21" rot="R90">3V3</text>
<text x="-24.765" y="14.605" size="0.6096" layer="21" rot="R90">NC</text>
<text x="-18.415" y="14.605" size="1.27" layer="21">B8</text>
<text x="-18.415" y="12.065" size="0.8128" layer="21">B9</text>
<text x="-18.415" y="9.525" size="1.27" layer="21">B10</text>
<text x="-18.415" y="6.985" size="1.27" layer="21">B11</text>
<text x="-18.415" y="4.445" size="1.27" layer="21">E2</text>
<wire x1="-19.05" y1="4.445" x2="-19.05" y2="5.715" width="0.127" layer="21"/>
<text x="-18.415" y="1.905" size="1.27" layer="21">E3</text>
<text x="-18.415" y="-0.635" size="1.27" layer="21">E4</text>
<text x="-18.415" y="-3.175" size="1.27" layer="21">E5</text>
<text x="-18.415" y="-8.255" size="1.27" layer="21">E20</text>
<text x="-18.415" y="-10.795" size="1.27" layer="21">E21</text>
<text x="-18.415" y="-13.335" size="1.27" layer="21">E22</text>
<text x="-18.415" y="-15.875" size="1.27" layer="21">E23</text>
<text x="-18.415" y="-20.955" size="1.27" layer="21">E30</text>
<text x="-18.415" y="-18.415" size="1.27" layer="21">E29</text>
<wire x1="23.495" y1="0" x2="22.225" y2="0" width="0.127" layer="21"/>
<wire x1="26.035" y1="0" x2="24.765" y2="0" width="0.127" layer="21"/>
<wire x1="24.13" y1="24.765" x2="23.495" y2="25.4" width="0.127" layer="21"/>
<wire x1="23.495" y1="25.4" x2="22.225" y2="25.4" width="0.127" layer="21"/>
<wire x1="24.765" y1="25.4" x2="24.13" y2="24.765" width="0.127" layer="21"/>
<wire x1="26.035" y1="25.4" x2="24.765" y2="25.4" width="0.127" layer="21"/>
<wire x1="23.495" y1="0" x2="24.13" y2="0.635" width="0.127" layer="21"/>
<wire x1="24.13" y1="0.635" x2="24.765" y2="0" width="0.127" layer="21"/>
<pad name="PTC12" x="22.86" y="1.27" drill="0.8" shape="square"/>
<pad name="PTC13" x="22.86" y="3.81" drill="0.8" shape="square"/>
<pad name="PTC16" x="22.86" y="6.35" drill="0.8" shape="square"/>
<pad name="PTC17" x="22.86" y="8.89" drill="0.8" shape="square"/>
<pad name="PTA16" x="22.86" y="11.43" drill="0.8" shape="square"/>
<pad name="PTA17" x="22.86" y="13.97" drill="0.8" shape="square"/>
<pad name="PTE31" x="22.86" y="16.51" drill="0.8" shape="square"/>
<pad name="PTD7" x="22.86" y="24.13" drill="0.8" shape="square"/>
<pad name="D15" x="25.4" y="24.13" drill="0.8" shape="square"/>
<pad name="GND2" x="25.4" y="16.51" drill="0.8" shape="square"/>
<pad name="D13" x="25.4" y="13.97" drill="0.8" shape="square"/>
<pad name="D12" x="25.4" y="11.43" drill="0.8" shape="square"/>
<pad name="D11" x="25.4" y="8.89" drill="0.8" shape="square"/>
<pad name="D10" x="25.4" y="6.35" drill="0.8" shape="square"/>
<pad name="D9" x="25.4" y="3.81" drill="0.8" shape="square"/>
<pad name="D8" x="25.4" y="1.27" drill="0.8" shape="square"/>
<pad name="PTD5" x="22.86" y="19.05" drill="0.8" shape="square"/>
<pad name="PTD6" x="22.86" y="21.59" drill="0.8" shape="square"/>
<pad name="D14" x="25.4" y="21.59" drill="0.8" shape="square"/>
<pad name="AREF" x="25.4" y="19.05" drill="0.8" shape="square"/>
<wire x1="26.035" y1="20.32" x2="26.67" y2="20.955" width="0.127" layer="21"/>
<wire x1="26.035" y1="22.86" x2="26.67" y2="23.495" width="0.127" layer="21"/>
<wire x1="21.59" y1="23.495" x2="22.225" y2="22.86" width="0.127" layer="21"/>
<wire x1="21.59" y1="20.955" x2="22.225" y2="20.32" width="0.127" layer="21"/>
<wire x1="21.59" y1="19.685" x2="21.59" y2="18.415" width="0.127" layer="21"/>
<wire x1="21.59" y1="22.225" x2="21.59" y2="20.955" width="0.127" layer="21"/>
<wire x1="26.67" y1="24.765" x2="26.67" y2="23.495" width="0.127" layer="21"/>
<wire x1="21.59" y1="24.765" x2="21.59" y2="23.495" width="0.127" layer="21"/>
<wire x1="26.67" y1="20.955" x2="26.67" y2="22.225" width="0.127" layer="21"/>
<wire x1="26.67" y1="18.415" x2="26.67" y2="19.685" width="0.127" layer="21"/>
<wire x1="22.225" y1="20.32" x2="21.59" y2="19.685" width="0.127" layer="21"/>
<wire x1="22.225" y1="22.86" x2="21.59" y2="22.225" width="0.127" layer="21"/>
<wire x1="26.67" y1="22.225" x2="26.035" y2="22.86" width="0.127" layer="21"/>
<wire x1="26.67" y1="19.685" x2="26.035" y2="20.32" width="0.127" layer="21"/>
<text x="17.145" y="23.495" size="1.27" layer="21">D7</text>
<text x="17.145" y="20.955" size="1.27" layer="21">D6</text>
<text x="17.145" y="18.415" size="1.27" layer="21">D5</text>
<text x="17.145" y="15.875" size="1.27" layer="21">E31</text>
<text x="17.145" y="13.335" size="1.27" layer="21">A17</text>
<text x="17.145" y="10.795" size="1.27" layer="21">A16</text>
<text x="17.145" y="8.255" size="1.27" layer="21">C17</text>
<text x="17.145" y="5.715" size="1.27" layer="21">C16</text>
<text x="17.145" y="3.175" size="1.27" layer="21">C13</text>
<text x="17.145" y="0.635" size="1.27" layer="21">C12</text>
</package>
</packages>
<symbols>
<symbol name="FRDM-KL25Z">
<description>FRDM-KL25Z</description>
<text x="-35.56" y="43.18" size="1.778" layer="94">FRDM-KL25Z</text>
<pin name="D7" x="55.88" y="-12.7" length="middle" rot="R180"/>
<wire x1="33.02" y1="-10.16" x2="33.02" y2="-50.8" width="0.254" layer="94"/>
<wire x1="33.02" y1="-50.8" x2="50.8" y2="-50.8" width="0.254" layer="94"/>
<wire x1="50.8" y1="-50.8" x2="50.8" y2="-10.16" width="0.254" layer="94"/>
<wire x1="50.8" y1="-10.16" x2="33.02" y2="-10.16" width="0.254" layer="94"/>
<text x="33.02" y="-7.62" size="1.778" layer="94">J1</text>
<pin name="D6" x="55.88" y="-17.78" length="middle" rot="R180"/>
<pin name="D5" x="55.88" y="-22.86" length="middle" rot="R180"/>
<pin name="D4" x="55.88" y="-27.94" length="middle" rot="R180"/>
<pin name="D3" x="55.88" y="-33.02" length="middle" rot="R180"/>
<pin name="D2" x="55.88" y="-38.1" length="middle" rot="R180"/>
<pin name="D1" x="55.88" y="-43.18" length="middle" rot="R180"/>
<pin name="PTC11" x="27.94" y="-12.7" length="middle"/>
<pin name="PTC10" x="27.94" y="-17.78" length="middle"/>
<pin name="PTC5" x="27.94" y="-27.94" length="middle"/>
<pin name="PTC4" x="27.94" y="-33.02" length="middle"/>
<pin name="PTC3" x="27.94" y="-38.1" length="middle"/>
<pin name="PTC0" x="27.94" y="-43.18" length="middle"/>
<pin name="PTC7" x="27.94" y="-48.26" length="middle"/>
<pin name="D0" x="55.88" y="-48.26" length="middle" rot="R180"/>
<pin name="PTC6" x="27.94" y="-22.86" length="middle"/>
<wire x1="-40.64" y1="-20.32" x2="-40.64" y2="-50.8" width="0.254" layer="94"/>
<wire x1="-40.64" y1="-50.8" x2="-20.32" y2="-50.8" width="0.254" layer="94"/>
<wire x1="-20.32" y1="-50.8" x2="-20.32" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-20.32" y1="-20.32" x2="-40.64" y2="-20.32" width="0.254" layer="94"/>
<text x="-40.64" y="-17.78" size="1.778" layer="94">J10</text>
<pin name="PTE20" x="-15.24" y="-22.86" length="middle" rot="R180"/>
<pin name="PTE21" x="-15.24" y="-27.94" length="middle" rot="R180"/>
<pin name="PTE22" x="-15.24" y="-33.02" length="middle" rot="R180"/>
<pin name="PTE23" x="-15.24" y="-38.1" length="middle" rot="R180"/>
<pin name="PTE29" x="-15.24" y="-43.18" length="middle" rot="R180"/>
<pin name="A1" x="-45.72" y="-27.94" length="middle"/>
<pin name="A2" x="-45.72" y="-33.02" length="middle"/>
<pin name="A3" x="-45.72" y="-38.1" length="middle"/>
<pin name="A4" x="-45.72" y="-43.18" length="middle"/>
<pin name="A5" x="-45.72" y="-48.26" length="middle"/>
<pin name="PTE30" x="-15.24" y="-48.26" length="middle" rot="R180"/>
<pin name="A0" x="-45.72" y="-22.86" length="middle"/>
<pin name="AREF" x="55.88" y="35.56" length="middle" rot="R180"/>
<wire x1="33.02" y1="48.26" x2="33.02" y2="-2.54" width="0.254" layer="94"/>
<wire x1="33.02" y1="-2.54" x2="50.8" y2="-2.54" width="0.254" layer="94"/>
<wire x1="50.8" y1="-2.54" x2="50.8" y2="48.26" width="0.254" layer="94"/>
<wire x1="50.8" y1="48.26" x2="33.02" y2="48.26" width="0.254" layer="94"/>
<text x="33.02" y="50.8" size="1.778" layer="94">J2</text>
<pin name="GND2" x="55.88" y="30.48" length="middle" rot="R180"/>
<pin name="D13" x="55.88" y="25.4" length="middle" rot="R180"/>
<pin name="D12" x="55.88" y="20.32" length="middle" rot="R180"/>
<pin name="D11" x="55.88" y="15.24" length="middle" rot="R180"/>
<pin name="D10" x="55.88" y="10.16" length="middle" rot="R180"/>
<pin name="D9" x="55.88" y="5.08" length="middle" rot="R180"/>
<pin name="PTD5" x="27.94" y="35.56" length="middle"/>
<pin name="PTE31" x="27.94" y="30.48" length="middle"/>
<pin name="PTA16" x="27.94" y="20.32" length="middle"/>
<pin name="PTC17" x="27.94" y="15.24" length="middle"/>
<pin name="PTC16" x="27.94" y="10.16" length="middle"/>
<pin name="PTC13" x="27.94" y="5.08" length="middle"/>
<pin name="PTC12" x="27.94" y="0" length="middle"/>
<pin name="D8" x="55.88" y="0" length="middle" rot="R180"/>
<pin name="PTA17" x="27.94" y="25.4" length="middle"/>
<pin name="D14" x="55.88" y="40.64" length="middle" rot="R180"/>
<pin name="D15" x="55.88" y="45.72" length="middle" rot="R180"/>
<pin name="PTD7" x="27.94" y="45.72" length="middle"/>
<pin name="PTD6" x="27.94" y="40.64" length="middle"/>
<pin name="PTB8" x="-15.24" y="25.4" length="middle" rot="R180"/>
<wire x1="-40.64" y1="27.94" x2="-40.64" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-40.64" y1="-12.7" x2="-20.32" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-20.32" y1="-12.7" x2="-20.32" y2="27.94" width="0.254" layer="94"/>
<wire x1="-20.32" y1="27.94" x2="-40.64" y2="27.94" width="0.254" layer="94"/>
<text x="-35.56" y="30.48" size="1.778" layer="94">J9</text>
<pin name="PTB9" x="-15.24" y="20.32" length="middle" rot="R180"/>
<pin name="PTB10" x="-15.24" y="15.24" length="middle" rot="R180"/>
<pin name="PTB11" x="-15.24" y="10.16" length="middle" rot="R180"/>
<pin name="PTE2" x="-15.24" y="5.08" length="middle" rot="R180"/>
<pin name="PTE3" x="-15.24" y="0" length="middle" rot="R180"/>
<pin name="PTE4" x="-15.24" y="-5.08" length="middle" rot="R180"/>
<pin name="NC" x="-45.72" y="25.4" length="middle"/>
<pin name="IOREF" x="-45.72" y="20.32" length="middle"/>
<pin name="3V3" x="-45.72" y="10.16" length="middle"/>
<pin name="5V" x="-45.72" y="5.08" length="middle"/>
<pin name="GND1" x="-45.72" y="0" length="middle"/>
<pin name="GND0" x="-45.72" y="-5.08" length="middle"/>
<pin name="VIN" x="-45.72" y="-10.16" length="middle"/>
<pin name="PTE5" x="-15.24" y="-10.16" length="middle" rot="R180"/>
<pin name="RST" x="-45.72" y="15.24" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRDM-KL25Z" prefix="FRDM">
<description>For creating FRDM-KL25Z shields</description>
<gates>
<gate name="G$1" symbol="FRDM-KL25Z" x="-5.08" y="2.54"/>
</gates>
<devices>
<device name="" package="FRDM-KL25Z">
<connects>
<connect gate="G$1" pin="3V3" pad="P3V3"/>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="A0" pad="A0"/>
<connect gate="G$1" pin="A1" pad="A1"/>
<connect gate="G$1" pin="A2" pad="A2"/>
<connect gate="G$1" pin="A3" pad="A3"/>
<connect gate="G$1" pin="A4" pad="A4"/>
<connect gate="G$1" pin="A5" pad="A5"/>
<connect gate="G$1" pin="AREF" pad="AREF"/>
<connect gate="G$1" pin="D0" pad="D0"/>
<connect gate="G$1" pin="D1" pad="D1"/>
<connect gate="G$1" pin="D10" pad="D10"/>
<connect gate="G$1" pin="D11" pad="D11"/>
<connect gate="G$1" pin="D12" pad="D12"/>
<connect gate="G$1" pin="D13" pad="D13"/>
<connect gate="G$1" pin="D14" pad="D14"/>
<connect gate="G$1" pin="D15" pad="D15"/>
<connect gate="G$1" pin="D2" pad="D2"/>
<connect gate="G$1" pin="D3" pad="D3"/>
<connect gate="G$1" pin="D4" pad="D4"/>
<connect gate="G$1" pin="D5" pad="D5"/>
<connect gate="G$1" pin="D6" pad="D6"/>
<connect gate="G$1" pin="D7" pad="D7"/>
<connect gate="G$1" pin="D8" pad="D8"/>
<connect gate="G$1" pin="D9" pad="D9"/>
<connect gate="G$1" pin="GND0" pad="GND0"/>
<connect gate="G$1" pin="GND1" pad="GND1"/>
<connect gate="G$1" pin="GND2" pad="GND2"/>
<connect gate="G$1" pin="IOREF" pad="3V3"/>
<connect gate="G$1" pin="NC" pad="NC"/>
<connect gate="G$1" pin="PTA16" pad="PTA16"/>
<connect gate="G$1" pin="PTA17" pad="PTA17"/>
<connect gate="G$1" pin="PTB10" pad="PTB10"/>
<connect gate="G$1" pin="PTB11" pad="PTB11"/>
<connect gate="G$1" pin="PTB8" pad="PTB8"/>
<connect gate="G$1" pin="PTB9" pad="PTB9"/>
<connect gate="G$1" pin="PTC0" pad="PTC0"/>
<connect gate="G$1" pin="PTC10" pad="PTC10"/>
<connect gate="G$1" pin="PTC11" pad="PTC11"/>
<connect gate="G$1" pin="PTC12" pad="PTC12"/>
<connect gate="G$1" pin="PTC13" pad="PTC13"/>
<connect gate="G$1" pin="PTC16" pad="PTC16"/>
<connect gate="G$1" pin="PTC17" pad="PTC17"/>
<connect gate="G$1" pin="PTC3" pad="PTC3"/>
<connect gate="G$1" pin="PTC4" pad="PTC4"/>
<connect gate="G$1" pin="PTC5" pad="PTC5"/>
<connect gate="G$1" pin="PTC6" pad="PTC6"/>
<connect gate="G$1" pin="PTC7" pad="PTC7"/>
<connect gate="G$1" pin="PTD5" pad="PTD5"/>
<connect gate="G$1" pin="PTD6" pad="PTD6"/>
<connect gate="G$1" pin="PTD7" pad="PTD7"/>
<connect gate="G$1" pin="PTE2" pad="PTE2"/>
<connect gate="G$1" pin="PTE20" pad="PTE20"/>
<connect gate="G$1" pin="PTE21" pad="PTE21"/>
<connect gate="G$1" pin="PTE22" pad="PTE22"/>
<connect gate="G$1" pin="PTE23" pad="PTE23"/>
<connect gate="G$1" pin="PTE29" pad="PTE29"/>
<connect gate="G$1" pin="PTE3" pad="PTE3"/>
<connect gate="G$1" pin="PTE30" pad="PTE30"/>
<connect gate="G$1" pin="PTE31" pad="PTE31"/>
<connect gate="G$1" pin="PTE4" pad="PTE4"/>
<connect gate="G$1" pin="PTE5" pad="PTE5"/>
<connect gate="G$1" pin="RST" pad="RESET"/>
<connect gate="G$1" pin="VIN" pad="VIN"/>
</connects>
<technologies>
<technology name="ARDUINO"/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="VCC">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="VCC" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="VCC" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="VCC" symbol="VCC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-molex">
<description>&lt;b&gt;Molex Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="KK-156-2">
<description>&lt;b&gt;KK 156 HEADER&lt;/b&gt;&lt;p&gt;
Source: http://www.molex.com/pdm_docs/sd/026604100_sd.pdf</description>
<wire x1="3.81" y1="4.95" x2="2.01" y2="4.95" width="0.2032" layer="21"/>
<wire x1="2.01" y1="4.95" x2="-1.985" y2="4.95" width="0.2032" layer="21"/>
<wire x1="-1.985" y1="4.95" x2="-3.785" y2="4.95" width="0.2032" layer="21"/>
<wire x1="-3.785" y1="4.95" x2="-3.785" y2="-4.825" width="0.2032" layer="21"/>
<wire x1="-3.785" y1="-4.825" x2="3.81" y2="-4.825" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-4.825" x2="3.81" y2="4.95" width="0.2032" layer="21"/>
<wire x1="-1.985" y1="2.525" x2="2.01" y2="2.525" width="0.2032" layer="21"/>
<wire x1="2.01" y1="2.525" x2="2.01" y2="4.95" width="0.2032" layer="21"/>
<wire x1="-1.985" y1="2.525" x2="-1.985" y2="4.95" width="0.2032" layer="21"/>
<pad name="1" x="-1.98" y="0" drill="1.7" diameter="2.1844" shape="long" rot="R90"/>
<pad name="2" x="1.98" y="0" drill="1.7" diameter="2.1844" shape="long" rot="R90"/>
<text x="-4.48" y="-4.445" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="5.75" y="-4.445" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MV">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-0.762" y="1.397" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="KK-156-2" prefix="X" uservalue="yes">
<description>&lt;b&gt;KK 156 HEADER&lt;/b&gt;&lt;p&gt;
Source: http://www.molex.com/pdm_docs/sd/026604100_sd.pdf</description>
<gates>
<gate name="-1" symbol="MV" x="0" y="2.54" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="MV" x="0" y="-2.54" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="KK-156-2">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ic-package">
<description>&lt;b&gt;IC Packages an Sockets&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL14">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="8.89" y1="2.921" x2="-8.89" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-2.921" x2="8.89" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="8.89" y1="2.921" x2="8.89" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="2.921" x2="-8.89" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-2.921" x2="-8.89" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="1.016" x2="-8.89" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-7.62" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-5.08" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="7.62" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="7.62" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-2.54" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="0" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="5.08" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="2.54" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="5.08" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="2.54" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="0" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="-2.54" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="-5.08" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="-7.62" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-9.271" y="-3.048" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-6.731" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SOCKET-14">
<description>&lt;b&gt;Dual In Line Socket&lt;/b&gt;</description>
<wire x1="8.89" y1="5.08" x2="-8.89" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-5.08" x2="8.89" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="8.89" y1="5.08" x2="8.89" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="5.08" x2="-8.89" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-5.08" x2="-8.89" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="1.016" x2="-8.89" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<wire x1="-8.89" y1="2.54" x2="8.89" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="2.54" x2="-8.89" y2="1.016" width="0.1524" layer="21"/>
<wire x1="8.89" y1="2.54" x2="8.89" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-2.54" x2="8.89" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-2.54" x2="-8.89" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="8.89" y1="-2.54" x2="8.89" y2="-5.08" width="0.1524" layer="21"/>
<pad name="1" x="-7.62" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-5.08" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="2.54" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="5.08" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-2.54" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="0" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="7.62" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="7.62" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="5.08" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="2.54" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="0" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="-2.54" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="-5.08" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="-7.62" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-5.715" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-9.144" y="-3.937" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="DIL14">
<wire x1="-5.08" y1="8.89" x2="-5.08" y2="-8.89" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-8.89" x2="5.08" y2="-8.89" width="0.254" layer="94"/>
<wire x1="5.08" y1="-8.89" x2="5.08" y2="8.89" width="0.254" layer="94"/>
<wire x1="5.08" y1="8.89" x2="2.54" y2="8.89" width="0.254" layer="94"/>
<wire x1="-5.08" y1="8.89" x2="-2.54" y2="8.89" width="0.254" layer="94"/>
<wire x1="-2.54" y1="8.89" x2="2.54" y2="8.89" width="0.254" layer="94" curve="180"/>
<text x="-4.445" y="9.525" size="1.778" layer="95">&gt;NAME</text>
<text x="-4.445" y="-11.43" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="7.62" visible="pad" length="short" direction="pas"/>
<pin name="2" x="-7.62" y="5.08" visible="pad" length="short" direction="pas"/>
<pin name="3" x="-7.62" y="2.54" visible="pad" length="short" direction="pas"/>
<pin name="4" x="-7.62" y="0" visible="pad" length="short" direction="pas"/>
<pin name="5" x="-7.62" y="-2.54" visible="pad" length="short" direction="pas"/>
<pin name="6" x="-7.62" y="-5.08" visible="pad" length="short" direction="pas"/>
<pin name="7" x="-7.62" y="-7.62" visible="pad" length="short" direction="pas"/>
<pin name="8" x="7.62" y="-7.62" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="9" x="7.62" y="-5.08" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="10" x="7.62" y="-2.54" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="11" x="7.62" y="0" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="12" x="7.62" y="2.54" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="13" x="7.62" y="5.08" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="14" x="7.62" y="7.62" visible="pad" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DIL14" prefix="IC" uservalue="yes">
<description>&lt;b&gt;Dual In Line / Socket&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="DIL14" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIL14">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="S" package="SOCKET-14">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="jumper">
<description>&lt;b&gt;Jumpers&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="JP1">
<description>&lt;b&gt;JUMPER&lt;/b&gt;</description>
<wire x1="-1.016" y1="0" x2="-1.27" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="0" x2="-1.27" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0" x2="1.27" y2="0.254" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0" x2="1.27" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.254" x2="1.27" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-2.54" x2="1.27" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="1.27" y1="2.286" x2="1.016" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.27" y1="2.286" x2="1.27" y2="0.254" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.54" x2="-1.016" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="2.286" x2="-1.016" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="2.286" x2="-1.27" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-0.254" x2="-1.27" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-2.54" x2="-1.27" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-2.54" x2="1.016" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="0" y="-1.27" drill="0.9144" shape="long"/>
<pad name="2" x="0" y="1.27" drill="0.9144" shape="long"/>
<text x="-1.651" y="-2.54" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="2.921" y="-2.54" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-0.3048" y1="0.9652" x2="0.3048" y2="1.5748" layer="51"/>
<rectangle x1="-0.3048" y1="-1.5748" x2="0.3048" y2="-0.9652" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="J1">
<wire x1="0" y1="2.54" x2="0" y2="3.81" width="0.4064" layer="94"/>
<wire x1="0" y1="3.81" x2="0" y2="5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-3.81" width="0.4064" layer="94"/>
<wire x1="0" y1="-3.81" x2="0" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="-1.905" y1="5.08" x2="1.905" y2="5.08" width="0.4064" layer="94"/>
<wire x1="1.905" y1="5.08" x2="1.905" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.905" y1="-5.08" x2="-1.905" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-1.905" y1="-5.08" x2="-1.905" y2="5.08" width="0.4064" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="4.445" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="1" x="0" y="-7.62" visible="pad" length="short" direction="pas" rot="R90"/>
<pin name="2" x="0" y="7.62" visible="pad" length="short" direction="pas" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="JP1Q" prefix="JP" uservalue="yes">
<description>&lt;b&gt;JUMPER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="J1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="JP1">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="eagle-ltspice">
<description>Default symbols for import LTspice schematics&lt;p&gt;
2012-10-29 alf@cadsoft.de&lt;br&gt;</description>
<packages>
<package name="0204/7">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
type 0204, grid 7.5 mm</description>
<wire x1="3.81" y1="0" x2="2.921" y2="0" width="0.508" layer="51"/>
<wire x1="-3.81" y1="0" x2="-2.921" y2="0" width="0.508" layer="51"/>
<wire x1="-2.54" y1="0.762" x2="-2.286" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.54" y1="-0.762" x2="-2.286" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="-0.762" width="0.1524" layer="21" curve="90"/>
<wire x1="2.286" y1="1.016" x2="2.54" y2="0.762" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="1.016" x2="-1.905" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="0.889" x2="-1.905" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="-1.016" x2="-1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="-0.889" x2="-1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.778" y1="0.889" x2="1.905" y2="1.016" width="0.1524" layer="21"/>
<wire x1="1.778" y1="0.889" x2="-1.778" y2="0.889" width="0.1524" layer="21"/>
<wire x1="1.778" y1="-0.889" x2="1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.778" y1="-0.889" x2="-1.778" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.016" x2="1.905" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.016" x2="1.905" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="2.54" y2="0.762" width="0.1524" layer="21"/>
<rectangle x1="2.54" y1="-0.254" x2="2.921" y2="0.254" layer="21"/>
<rectangle x1="-2.921" y1="-0.254" x2="-2.54" y2="0.254" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="3.81" y="0" drill="0.8128" shape="octagon"/>
<text x="-2.54" y="1.2954" size="0.9906" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.6256" y="-0.4826" size="0.9906" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="0207/10">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
type 0207, grid 10 mm</description>
<wire x1="5.08" y1="0" x2="4.064" y2="0" width="0.6096" layer="51"/>
<wire x1="-5.08" y1="0" x2="-4.064" y2="0" width="0.6096" layer="51"/>
<wire x1="-3.175" y1="0.889" x2="-2.921" y2="1.143" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.175" y1="-0.889" x2="-2.921" y2="-1.143" width="0.1524" layer="21" curve="90"/>
<wire x1="2.921" y1="-1.143" x2="3.175" y2="-0.889" width="0.1524" layer="21" curve="90"/>
<wire x1="2.921" y1="1.143" x2="3.175" y2="0.889" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.175" y1="-0.889" x2="-3.175" y2="0.889" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="1.143" x2="-2.54" y2="1.143" width="0.1524" layer="21"/>
<wire x1="-2.413" y1="1.016" x2="-2.54" y2="1.143" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="-1.143" x2="-2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="-2.413" y1="-1.016" x2="-2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="2.413" y1="1.016" x2="2.54" y2="1.143" width="0.1524" layer="21"/>
<wire x1="2.413" y1="1.016" x2="-2.413" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.413" y1="-1.016" x2="2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="2.413" y1="-1.016" x2="-2.413" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.921" y1="1.143" x2="2.54" y2="1.143" width="0.1524" layer="21"/>
<wire x1="2.921" y1="-1.143" x2="2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-0.889" x2="3.175" y2="0.889" width="0.1524" layer="21"/>
<rectangle x1="3.175" y1="-0.3048" x2="4.0386" y2="0.3048" layer="21"/>
<rectangle x1="-4.0386" y1="-0.3048" x2="-3.175" y2="0.3048" layer="21"/>
<pad name="1" x="-5.08" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="5.08" y="0" drill="0.8128" shape="octagon"/>
<text x="-3.048" y="1.524" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.2606" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="R0201">
<description>&lt;b&gt;RESISTOR&lt;/b&gt; chip&lt;p&gt;
Source: http://www.vishay.com/docs/20008/dcrcw.pdf</description>
<rectangle x1="-0.3" y1="-0.15" x2="-0.15" y2="0.15" layer="51"/>
<rectangle x1="0.15" y1="-0.15" x2="0.3" y2="0.15" layer="51"/>
<rectangle x1="-0.15" y1="-0.15" x2="0.15" y2="0.15" layer="21"/>
<smd name="1" x="-0.255" y="0" dx="0.28" dy="0.43" layer="1"/>
<smd name="2" x="0.255" y="0" dx="0.28" dy="0.43" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R0402">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R0603">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.432" y1="-0.356" x2="0.432" y2="-0.356" width="0.1524" layer="51"/>
<wire x1="0.432" y1="0.356" x2="-0.432" y2="0.356" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<rectangle x1="0.4318" y1="-0.4318" x2="0.8382" y2="0.4318" layer="51"/>
<rectangle x1="-0.8382" y1="-0.4318" x2="-0.4318" y2="0.4318" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
<smd name="1" x="-0.85" y="0" dx="1" dy="1.1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1" dy="1.1" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R0805">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;</description>
<wire x1="-0.41" y1="0.635" x2="0.41" y2="0.635" width="0.1524" layer="51"/>
<wire x1="-0.41" y1="-0.635" x2="0.41" y2="-0.635" width="0.1524" layer="51"/>
<wire x1="-1.973" y1="0.983" x2="1.973" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.973" y1="0.983" x2="1.973" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.973" y1="-0.983" x2="-1.973" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.973" y1="-0.983" x2="-1.973" y2="0.983" width="0.0508" layer="39"/>
<rectangle x1="0.4064" y1="-0.6985" x2="1.0564" y2="0.7015" layer="51"/>
<rectangle x1="-1.0668" y1="-0.6985" x2="-0.4168" y2="0.7015" layer="51"/>
<rectangle x1="-0.1999" y1="-0.5001" x2="0.1999" y2="0.5001" layer="35"/>
<smd name="1" x="-0.95" y="0" dx="1.3" dy="1.5" layer="1"/>
<smd name="2" x="0.95" y="0" dx="1.3" dy="1.5" layer="1"/>
<text x="-0.635" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R1005">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R1206">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="0.9525" y1="-0.8128" x2="-0.9652" y2="-0.8128" width="0.1524" layer="51"/>
<wire x1="0.9525" y1="0.8128" x2="-0.9652" y2="0.8128" width="0.1524" layer="51"/>
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<rectangle x1="-1.6891" y1="-0.8763" x2="-0.9525" y2="0.8763" layer="51"/>
<rectangle x1="0.9525" y1="-0.8763" x2="1.6891" y2="0.8763" layer="51"/>
<rectangle x1="-0.3" y1="-0.7" x2="0.3" y2="0.7" layer="35"/>
<smd name="1" x="-1.422" y="0" dx="1.6" dy="1.803" layer="1"/>
<smd name="2" x="1.422" y="0" dx="1.6" dy="1.803" layer="1"/>
<text x="-1.27" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R1210">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.913" y1="1.219" x2="0.939" y2="1.219" width="0.1524" layer="51"/>
<wire x1="-0.913" y1="-1.219" x2="0.939" y2="-1.219" width="0.1524" layer="51"/>
<wire x1="-2.473" y1="1.483" x2="2.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="2.473" y1="1.483" x2="2.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-1.483" x2="-2.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-1.483" x2="-2.473" y2="1.483" width="0.0508" layer="39"/>
<rectangle x1="-1.651" y1="-1.3081" x2="-0.9009" y2="1.2918" layer="51"/>
<rectangle x1="0.9144" y1="-1.3081" x2="1.6645" y2="1.2918" layer="51"/>
<rectangle x1="-0.3" y1="-0.8999" x2="0.3" y2="0.8999" layer="35"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="2.7" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="2.7" layer="1"/>
<text x="-2.54" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R1218">
<description>&lt;b&gt;CRCW1218 Thick Film, Rectangular Chip Resistors&lt;/b&gt;&lt;p&gt;
Source: http://www.vishay.com .. dcrcw.pdf</description>
<wire x1="-0.913" y1="-2.219" x2="0.939" y2="-2.219" width="0.1524" layer="51"/>
<wire x1="0.913" y1="2.219" x2="-0.939" y2="2.219" width="0.1524" layer="51"/>
<rectangle x1="-1.651" y1="-2.3" x2="-0.9009" y2="2.3" layer="51"/>
<rectangle x1="0.9144" y1="-2.3" x2="1.6645" y2="2.3" layer="51"/>
<smd name="1" x="-1.475" y="0" dx="1.05" dy="4.9" layer="1"/>
<smd name="2" x="1.475" y="0" dx="1.05" dy="4.9" layer="1"/>
<text x="-2.54" y="2.54" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.81" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R2010">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-1.662" y1="1.245" x2="1.662" y2="1.245" width="0.1524" layer="51"/>
<wire x1="-1.637" y1="-1.245" x2="1.687" y2="-1.245" width="0.1524" layer="51"/>
<wire x1="-3.473" y1="1.483" x2="3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="1.483" x2="3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-1.483" x2="-3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-1.483" x2="-3.473" y2="1.483" width="0.0508" layer="39"/>
<rectangle x1="-2.4892" y1="-1.3208" x2="-1.6393" y2="1.3292" layer="51"/>
<rectangle x1="1.651" y1="-1.3208" x2="2.5009" y2="1.3292" layer="51"/>
<smd name="1" x="-2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<smd name="2" x="2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<text x="-3.175" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.175" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R2012">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.41" y1="0.635" x2="0.41" y2="0.635" width="0.1524" layer="51"/>
<wire x1="-0.41" y1="-0.635" x2="0.41" y2="-0.635" width="0.1524" layer="51"/>
<wire x1="-1.973" y1="0.983" x2="1.973" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.973" y1="0.983" x2="1.973" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.973" y1="-0.983" x2="-1.973" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.973" y1="-0.983" x2="-1.973" y2="0.983" width="0.0508" layer="39"/>
<rectangle x1="0.4064" y1="-0.6985" x2="1.0564" y2="0.7015" layer="51"/>
<rectangle x1="-1.0668" y1="-0.6985" x2="-0.4168" y2="0.7015" layer="51"/>
<rectangle x1="-0.1001" y1="-0.5999" x2="0.1001" y2="0.5999" layer="35"/>
<smd name="1" x="-0.85" y="0" dx="1.3" dy="1.5" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.3" dy="1.5" layer="1"/>
<text x="-0.635" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R2512">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-2.362" y1="1.473" x2="2.387" y2="1.473" width="0.1524" layer="51"/>
<wire x1="-2.362" y1="-1.473" x2="2.387" y2="-1.473" width="0.1524" layer="51"/>
<wire x1="-3.973" y1="1.983" x2="3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="1.983" x2="3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="-1.983" x2="-3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-3.973" y1="-1.983" x2="-3.973" y2="1.983" width="0.0508" layer="39"/>
<rectangle x1="-3.2004" y1="-1.5494" x2="-2.3505" y2="1.5507" layer="51"/>
<rectangle x1="2.3622" y1="-1.5494" x2="3.2121" y2="1.5507" layer="51"/>
<rectangle x1="-0.5001" y1="-1" x2="0.5001" y2="1" layer="35"/>
<smd name="1" x="-2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<smd name="2" x="2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<text x="-2.54" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R3216">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.913" y1="0.8" x2="0.888" y2="0.8" width="0.1524" layer="51"/>
<wire x1="-0.913" y1="-0.8" x2="0.888" y2="-0.8" width="0.1524" layer="51"/>
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<rectangle x1="-1.651" y1="-0.8763" x2="-0.9009" y2="0.8738" layer="51"/>
<rectangle x1="0.889" y1="-0.8763" x2="1.6391" y2="0.8738" layer="51"/>
<rectangle x1="-0.3" y1="-0.7" x2="0.3" y2="0.7" layer="35"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-1.905" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R3225">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.913" y1="1.219" x2="0.939" y2="1.219" width="0.1524" layer="51"/>
<wire x1="-0.913" y1="-1.219" x2="0.939" y2="-1.219" width="0.1524" layer="51"/>
<wire x1="-2.473" y1="1.483" x2="2.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="2.473" y1="1.483" x2="2.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-1.483" x2="-2.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-1.483" x2="-2.473" y2="1.483" width="0.0508" layer="39"/>
<rectangle x1="-1.651" y1="-1.3081" x2="-0.9009" y2="1.2918" layer="51"/>
<rectangle x1="0.9144" y1="-1.3081" x2="1.6645" y2="1.2918" layer="51"/>
<rectangle x1="-0.3" y1="-1" x2="0.3" y2="1" layer="35"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="2.7" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="2.7" layer="1"/>
<text x="-2.54" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R4527">
<description>&lt;b&gt;Package 4527&lt;/b&gt;&lt;p&gt;
Source: http://www.vishay.com/docs/31059/wsrhigh.pdf</description>
<wire x1="-5.675" y1="-3.375" x2="5.65" y2="-3.375" width="0.2032" layer="21"/>
<wire x1="5.65" y1="-3.375" x2="5.65" y2="3.375" width="0.2032" layer="51"/>
<wire x1="5.65" y1="3.375" x2="-5.675" y2="3.375" width="0.2032" layer="21"/>
<wire x1="-5.675" y1="3.375" x2="-5.675" y2="-3.375" width="0.2032" layer="51"/>
<smd name="1" x="-4.575" y="0" dx="3.94" dy="5.84" layer="1"/>
<smd name="2" x="4.575" y="0" dx="3.94" dy="5.84" layer="1"/>
<text x="-5.715" y="3.81" size="1.27" layer="25">&gt;NAME</text>
<text x="-5.715" y="-5.08" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R5025">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-1.662" y1="1.245" x2="1.662" y2="1.245" width="0.1524" layer="51"/>
<wire x1="-1.637" y1="-1.245" x2="1.687" y2="-1.245" width="0.1524" layer="51"/>
<wire x1="-3.473" y1="1.483" x2="3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="1.483" x2="3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-1.483" x2="-3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-1.483" x2="-3.473" y2="1.483" width="0.0508" layer="39"/>
<rectangle x1="-2.4892" y1="-1.3208" x2="-1.6393" y2="1.3292" layer="51"/>
<rectangle x1="1.651" y1="-1.3208" x2="2.5009" y2="1.3292" layer="51"/>
<rectangle x1="-0.5001" y1="-1" x2="0.5001" y2="1" layer="35"/>
<smd name="1" x="-2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<smd name="2" x="2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<text x="-3.175" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.175" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="R6332">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
Source: http://download.siliconexpert.com/pdfs/2005/02/24/Semi_Ap/2/VSH/Resistor/dcrcwfre.pdf</description>
<wire x1="-2.362" y1="1.473" x2="2.387" y2="1.473" width="0.1524" layer="51"/>
<wire x1="-2.362" y1="-1.473" x2="2.387" y2="-1.473" width="0.1524" layer="51"/>
<wire x1="-3.973" y1="1.983" x2="3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="1.983" x2="3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="-1.983" x2="-3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-3.973" y1="-1.983" x2="-3.973" y2="1.983" width="0.0508" layer="39"/>
<rectangle x1="-3.2004" y1="-1.5494" x2="-2.3505" y2="1.5507" layer="51"/>
<rectangle x1="2.3622" y1="-1.5494" x2="3.2121" y2="1.5507" layer="51"/>
<rectangle x1="-0.5001" y1="-1" x2="0.5001" y2="1" layer="35"/>
<smd name="1" x="-3.1" y="0" dx="1" dy="3.2" layer="1"/>
<smd name="2" x="3.1" y="0" dx="1" dy="3.2" layer="1"/>
<text x="-2.54" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="R">
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<text x="-5.08" y="0" size="0.4064" layer="99" align="center">SpiceOrder 1</text>
<text x="5.08" y="0" size="0.4064" layer="99" align="center">SpiceOrder 2</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="R" prefix="R" uservalue="yes">
<description>&lt;B&gt;RESISTOR&lt;/B&gt;, European symbol</description>
<gates>
<gate name="G$1" symbol="R" x="0" y="0"/>
</gates>
<devices>
<device name="0204/7" package="0204/7">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="0207/10" package="0207/10">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R0201" package="R0201">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R0402" package="R0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R0603" package="R0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="" package="R0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R1005" package="R1005">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R1206" package="R1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R1210" package="R1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R1218" package="R1218">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R2010" package="R2010">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R2012" package="R2012">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R2512" package="R2512">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R3216" package="R3216">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R3225" package="R3225">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R4527" package="R4527">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R5025" package="R5025">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
<device name="R6332" package="R6332">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="SPICEMODEL" value="NONE" constant="no"/>
<attribute name="SPICEPREFIX" value="R" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Bluetooth HC-05">
<description>Bluetooth HC05 Module. See http://mcuoneclipse.com/2013/02/14/bluetooth-with-the-freedom-board/</description>
<packages>
<package name="BLUETOOTH_SMD">
<description>HC-05</description>
<wire x1="0" y1="1" x2="0" y2="9.5" width="0.127" layer="21"/>
<wire x1="0" y1="9.5" x2="13" y2="9.5" width="0.127" layer="21"/>
<wire x1="13" y1="9.5" x2="13" y2="1" width="0.127" layer="21"/>
<smd name="1" x="0" y="0" dx="2" dy="1" layer="1"/>
<smd name="2" x="0" y="-1.5" dx="2" dy="1" layer="1"/>
<smd name="3" x="0" y="-3" dx="2" dy="1" layer="1"/>
<smd name="4" x="0" y="-4.5" dx="2" dy="1" layer="1"/>
<smd name="5" x="0" y="-6" dx="2" dy="1" layer="1"/>
<smd name="6" x="0" y="-7.5" dx="2" dy="1" layer="1"/>
<smd name="7" x="0" y="-9" dx="2" dy="1" layer="1"/>
<smd name="8" x="0" y="-10.5" dx="2" dy="1" layer="1"/>
<smd name="9" x="0" y="-12" dx="2" dy="1" layer="1"/>
<smd name="10" x="0" y="-13.5" dx="2" dy="1" layer="1"/>
<smd name="11" x="0" y="-15" dx="2" dy="1" layer="1"/>
<smd name="12" x="0" y="-16.5" dx="2" dy="1" layer="1"/>
<smd name="13" x="0" y="-18" dx="2" dy="1" layer="1"/>
<smd name="22" x="13" y="-18" dx="2" dy="1" layer="1"/>
<smd name="23" x="13" y="-16.5" dx="2" dy="1" layer="1"/>
<smd name="24" x="13" y="-15" dx="2" dy="1" layer="1"/>
<smd name="25" x="13" y="-13.5" dx="2" dy="1" layer="1"/>
<smd name="26" x="13" y="-12" dx="2" dy="1" layer="1"/>
<smd name="27" x="13" y="-10.5" dx="2" dy="1" layer="1"/>
<smd name="28" x="13" y="-9" dx="2" dy="1" layer="1"/>
<smd name="29" x="13" y="-7.5" dx="2" dy="1" layer="1"/>
<smd name="30" x="13" y="-6" dx="2" dy="1" layer="1"/>
<smd name="31" x="13" y="-4.5" dx="2" dy="1" layer="1"/>
<smd name="32" x="13" y="-3" dx="2" dy="1" layer="1"/>
<smd name="33" x="13" y="-1.5" dx="2" dy="1" layer="1"/>
<smd name="34" x="13" y="0" dx="2" dy="1" layer="1"/>
<smd name="14" x="1.25" y="-19.75" dx="1.8" dy="1" layer="1" rot="R90"/>
<smd name="15" x="2.75" y="-19.75" dx="1.8" dy="1" layer="1" rot="R90"/>
<smd name="16" x="4.25" y="-19.75" dx="1.8" dy="1" layer="1" rot="R90"/>
<smd name="17" x="5.75" y="-19.75" dx="1.8" dy="1" layer="1" rot="R90"/>
<smd name="18" x="7.25" y="-19.75" dx="1.8" dy="1" layer="1" rot="R90"/>
<smd name="19" x="8.75" y="-19.75" dx="1.8" dy="1" layer="1" rot="R90"/>
<smd name="20" x="10.25" y="-19.75" dx="1.8" dy="1" layer="1" rot="R90"/>
<smd name="21" x="11.75" y="-19.75" dx="1.8" dy="1" layer="1" rot="R90"/>
<text x="1" y="7.5" size="1.27" layer="25">&gt;name</text>
</package>
</packages>
<symbols>
<symbol name="HC-05">
<wire x1="-17.78" y1="17.78" x2="-17.78" y2="-17.78" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-17.78" x2="20.32" y2="-17.78" width="0.254" layer="94"/>
<wire x1="20.32" y1="-17.78" x2="20.32" y2="17.78" width="0.254" layer="94"/>
<wire x1="20.32" y1="17.78" x2="-17.78" y2="17.78" width="0.254" layer="94"/>
<text x="-17.78" y="22.86" size="1.778" layer="95">&gt;NAME</text>
<text x="-17.78" y="20.32" size="1.778" layer="96">&gt;VALUE</text>
<pin name="TX" x="-22.86" y="15.24" length="middle"/>
<pin name="RX" x="-22.86" y="12.7" length="middle"/>
<pin name="CTS" x="-22.86" y="10.16" length="middle"/>
<pin name="RTS" x="-22.86" y="7.62" length="middle"/>
<pin name="PCM_CLK" x="-22.86" y="5.08" length="middle"/>
<pin name="PCM_OUT" x="-22.86" y="2.54" length="middle"/>
<pin name="PCM_IN" x="-22.86" y="0" length="middle"/>
<pin name="PCN_SYNC" x="-22.86" y="-2.54" length="middle"/>
<pin name="AIO0" x="-22.86" y="-5.08" length="middle"/>
<pin name="AIO1" x="-22.86" y="-7.62" length="middle"/>
<pin name="RST" x="-22.86" y="-10.16" length="middle"/>
<pin name="3V3" x="-22.86" y="-12.7" length="middle"/>
<pin name="GND" x="-22.86" y="-15.24" length="middle"/>
<pin name="NC" x="-7.62" y="-22.86" length="middle" rot="R90"/>
<pin name="VBUSD-" x="-5.08" y="-22.86" length="middle" rot="R90"/>
<pin name="CSB" x="-2.54" y="-22.86" length="middle" rot="R90"/>
<pin name="MOSI" x="0" y="-22.86" length="middle" rot="R90"/>
<pin name="MISO" x="2.54" y="-22.86" length="middle" rot="R90"/>
<pin name="CLK" x="5.08" y="-22.86" length="middle" rot="R90"/>
<pin name="VBUSD+" x="7.62" y="-22.86" length="middle" rot="R90"/>
<pin name="GND1" x="10.16" y="-22.86" length="middle" rot="R90"/>
<pin name="GND2" x="25.4" y="-15.24" length="middle" rot="R180"/>
<pin name="PIO0" x="25.4" y="-12.7" length="middle" rot="R180"/>
<pin name="PIO1" x="25.4" y="-10.16" length="middle" rot="R180"/>
<pin name="PIO2" x="25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="PIO3" x="25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="PIO4" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="PIO5" x="25.4" y="0" length="middle" rot="R180"/>
<pin name="PIO6" x="25.4" y="2.54" length="middle" rot="R180"/>
<pin name="PIO7" x="25.4" y="5.08" length="middle" rot="R180"/>
<pin name="PIO8" x="25.4" y="7.62" length="middle" rot="R180"/>
<pin name="PIO9" x="25.4" y="10.16" length="middle" rot="R180"/>
<pin name="PIO10" x="25.4" y="12.7" length="middle" rot="R180"/>
<pin name="PIO11" x="25.4" y="15.24" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="HC_05" prefix="U">
<description>HC-05 Bluetooth Module</description>
<gates>
<gate name="G$1" symbol="HC-05" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BLUETOOTH_SMD">
<connects>
<connect gate="G$1" pin="3V3" pad="12"/>
<connect gate="G$1" pin="AIO0" pad="9"/>
<connect gate="G$1" pin="AIO1" pad="10"/>
<connect gate="G$1" pin="CLK" pad="19"/>
<connect gate="G$1" pin="CSB" pad="16"/>
<connect gate="G$1" pin="CTS" pad="3"/>
<connect gate="G$1" pin="GND" pad="13"/>
<connect gate="G$1" pin="GND1" pad="21"/>
<connect gate="G$1" pin="GND2" pad="22"/>
<connect gate="G$1" pin="MISO" pad="18"/>
<connect gate="G$1" pin="MOSI" pad="17"/>
<connect gate="G$1" pin="NC" pad="14"/>
<connect gate="G$1" pin="PCM_CLK" pad="5"/>
<connect gate="G$1" pin="PCM_IN" pad="7"/>
<connect gate="G$1" pin="PCM_OUT" pad="6"/>
<connect gate="G$1" pin="PCN_SYNC" pad="8"/>
<connect gate="G$1" pin="PIO0" pad="23"/>
<connect gate="G$1" pin="PIO1" pad="24"/>
<connect gate="G$1" pin="PIO10" pad="33"/>
<connect gate="G$1" pin="PIO11" pad="34"/>
<connect gate="G$1" pin="PIO2" pad="25"/>
<connect gate="G$1" pin="PIO3" pad="26"/>
<connect gate="G$1" pin="PIO4" pad="27"/>
<connect gate="G$1" pin="PIO5" pad="28"/>
<connect gate="G$1" pin="PIO6" pad="29"/>
<connect gate="G$1" pin="PIO7" pad="30"/>
<connect gate="G$1" pin="PIO8" pad="31"/>
<connect gate="G$1" pin="PIO9" pad="32"/>
<connect gate="G$1" pin="RST" pad="11"/>
<connect gate="G$1" pin="RTS" pad="4"/>
<connect gate="G$1" pin="RX" pad="2"/>
<connect gate="G$1" pin="TX" pad="1"/>
<connect gate="G$1" pin="VBUSD+" pad="20"/>
<connect gate="G$1" pin="VBUSD-" pad="15"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="SV1" library="con-lstb" deviceset="MA12-2" device="" value="Radio"/>
<part name="FRDM1" library="Freedom" deviceset="FRDM-KL25Z" device="" technology="ARDUINO"/>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
<part name="P+2" library="supply1" deviceset="VCC" device="" value="3V3"/>
<part name="GND2" library="supply1" deviceset="GND" device=""/>
<part name="SV2" library="con-lstb" deviceset="MA08-2" device="" value="IR"/>
<part name="P+3" library="supply1" deviceset="VCC" device="" value="3V3"/>
<part name="GND3" library="supply1" deviceset="GND" device=""/>
<part name="SV3" library="con-lstb" deviceset="MA03-1" device="" value="S7V7F5"/>
<part name="IC1" library="ic-package" deviceset="DIL14" device="" value="DRV8835"/>
<part name="MOTORR" library="con-molex" deviceset="KK-156-2" device="" value="Right"/>
<part name="MOTORL" library="con-molex" deviceset="KK-156-2" device="" value="Left"/>
<part name="P+5" library="supply1" deviceset="VCC" device="" value="3V3"/>
<part name="GND4" library="supply1" deviceset="GND" device=""/>
<part name="X1" library="con-molex" deviceset="KK-156-2" device="" value="Bat"/>
<part name="JP1" library="jumper" deviceset="JP1Q" device="" value="PWR"/>
<part name="HC-SR04" library="con-lstb" deviceset="MA04-1" device="" value="SR04"/>
<part name="R1" library="eagle-ltspice" deviceset="R" device="" value="27k"/>
<part name="R3" library="eagle-ltspice" deviceset="R" device="" value="15k"/>
<part name="GND5" library="supply1" deviceset="GND" device=""/>
<part name="U1" library="Bluetooth HC-05" deviceset="HC_05" device=""/>
<part name="QUAD1" library="con-lstb" deviceset="MA04-1" device="" value="QUAD1"/>
<part name="SV5" library="con-lstb" deviceset="MA04-1" device="" value="QUAD2"/>
<part name="SV4" library="con-lstb" deviceset="MA03-1" device="" value="10cm"/>
<part name="SV6" library="con-lstb" deviceset="MA03-1" device="" value="10cm"/>
<part name="SV7" library="con-lstb" deviceset="MA03-1" device="" value="5cm"/>
<part name="SV8" library="con-lstb" deviceset="MA03-1" device="" value="5cm"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="SV1" gate="1" x="137.16" y="134.62"/>
<instance part="FRDM1" gate="G$1" x="-7.62" y="96.52"/>
<instance part="GND1" gate="1" x="-68.58" y="101.6" rot="R180"/>
<instance part="P+2" gate="VCC" x="167.64" y="127"/>
<instance part="GND2" gate="1" x="160.02" y="129.54" rot="R180"/>
<instance part="SV2" gate="G$1" x="99.06" y="91.44"/>
<instance part="P+3" gate="VCC" x="78.74" y="106.68"/>
<instance part="GND3" gate="1" x="83.82" y="106.68" rot="R180"/>
<instance part="SV3" gate="G$1" x="139.7" y="68.58"/>
<instance part="IC1" gate="G$1" x="81.28" y="187.96"/>
<instance part="MOTORR" gate="-1" x="129.54" y="200.66"/>
<instance part="MOTORR" gate="-2" x="129.54" y="195.58"/>
<instance part="MOTORL" gate="-1" x="129.54" y="187.96"/>
<instance part="MOTORL" gate="-2" x="129.54" y="182.88"/>
<instance part="P+5" gate="VCC" x="58.42" y="198.12"/>
<instance part="GND4" gate="1" x="63.5" y="205.74" rot="R180"/>
<instance part="X1" gate="-1" x="129.54" y="170.18"/>
<instance part="X1" gate="-2" x="129.54" y="165.1"/>
<instance part="JP1" gate="A" x="106.68" y="170.18" rot="R270"/>
<instance part="HC-SR04" gate="1" x="78.74" y="58.42"/>
<instance part="R1" gate="G$1" x="106.68" y="53.34" rot="R90"/>
<instance part="R3" gate="G$1" x="106.68" y="63.5" rot="R90"/>
<instance part="GND5" gate="1" x="106.68" y="43.18"/>
<instance part="U1" gate="G$1" x="-17.78" y="200.66"/>
<instance part="QUAD1" gate="1" x="-45.72" y="167.64"/>
<instance part="SV5" gate="1" x="-22.86" y="167.64"/>
<instance part="SV4" gate="G$1" x="-127" y="134.62"/>
<instance part="SV6" gate="G$1" x="-127" y="119.38"/>
<instance part="SV7" gate="G$1" x="-127" y="104.14"/>
<instance part="SV8" gate="G$1" x="-127" y="88.9"/>
</instances>
<busses>
</busses>
<nets>
<net name="RADIO_IRQ" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTA17"/>
<wire x1="20.32" y1="121.92" x2="-7.62" y2="121.92" width="0.1524" layer="91"/>
<label x="-2.54" y="121.92" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="2"/>
<wire x1="129.54" y1="121.92" x2="111.76" y2="121.92" width="0.1524" layer="91"/>
<label x="111.76" y="121.92" size="1.778" layer="95"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="P+2" gate="VCC" pin="VCC"/>
<wire x1="167.64" y1="124.46" x2="167.64" y2="121.92" width="0.1524" layer="91"/>
<pinref part="SV1" gate="1" pin="1"/>
<wire x1="144.78" y1="121.92" x2="167.64" y2="121.92" width="0.1524" layer="91"/>
<label x="152.4" y="121.92" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV2" gate="G$1" pin="4"/>
<wire x1="91.44" y1="86.36" x2="78.74" y2="86.36" width="0.1524" layer="91"/>
<wire x1="78.74" y1="86.36" x2="78.74" y2="104.14" width="0.1524" layer="91"/>
<pinref part="P+3" gate="VCC" pin="VCC"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="2"/>
<label x="66.04" y="193.04" size="1.778" layer="95"/>
<wire x1="73.66" y1="193.04" x2="58.42" y2="193.04" width="0.1524" layer="91"/>
<pinref part="P+5" gate="VCC" pin="VCC"/>
<wire x1="58.42" y1="193.04" x2="58.42" y2="195.58" width="0.1524" layer="91"/>
<junction x="58.42" y="193.04"/>
<wire x1="58.42" y1="193.04" x2="58.42" y2="180.34" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="7"/>
<label x="66.04" y="180.34" size="1.778" layer="95"/>
<wire x1="73.66" y1="180.34" x2="58.42" y2="180.34" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="HC-SR04" gate="1" pin="1"/>
<wire x1="86.36" y1="53.34" x2="96.52" y2="53.34" width="0.1524" layer="91"/>
<label x="88.9" y="53.34" size="1.778" layer="95"/>
</segment>
</net>
<net name="RADIO_ATTN" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE23"/>
<wire x1="-22.86" y1="58.42" x2="-7.62" y2="58.42" width="0.1524" layer="91"/>
<label x="-17.78" y="58.42" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="15"/>
<wire x1="144.78" y1="139.7" x2="160.02" y2="139.7" width="0.1524" layer="91"/>
<label x="147.32" y="139.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="RADIO_SPICLK" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTC5"/>
<wire x1="20.32" y1="68.58" x2="-2.54" y2="68.58" width="0.1524" layer="91"/>
<label x="-2.54" y="68.58" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="21"/>
<wire x1="144.78" y1="147.32" x2="160.02" y2="147.32" width="0.1524" layer="91"/>
<label x="147.32" y="147.32" size="1.778" layer="95"/>
</segment>
</net>
<net name="RADIO_RTXEN" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE22"/>
<wire x1="-22.86" y1="63.5" x2="-7.62" y2="63.5" width="0.1524" layer="91"/>
<label x="-17.78" y="63.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="20"/>
<wire x1="129.54" y1="144.78" x2="111.76" y2="144.78" width="0.1524" layer="91"/>
<label x="111.76" y="144.78" size="1.778" layer="95"/>
</segment>
</net>
<net name="RADIO_RES" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE21"/>
<wire x1="-22.86" y1="68.58" x2="-7.62" y2="68.58" width="0.1524" layer="91"/>
<label x="-17.78" y="68.58" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="13"/>
<wire x1="144.78" y1="137.16" x2="160.02" y2="137.16" width="0.1524" layer="91"/>
<label x="147.32" y="137.16" size="1.778" layer="95"/>
</segment>
</net>
<net name="RADIO_MOSI" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTC7"/>
<wire x1="20.32" y1="48.26" x2="2.54" y2="48.26" width="0.1524" layer="91"/>
<label x="2.54" y="48.26" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="17"/>
<wire x1="144.78" y1="142.24" x2="160.02" y2="142.24" width="0.1524" layer="91"/>
<label x="147.32" y="142.24" size="1.778" layer="95"/>
</segment>
</net>
<net name="RADIO_MISO" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTC6"/>
<wire x1="20.32" y1="73.66" x2="2.54" y2="73.66" width="0.1524" layer="91"/>
<label x="2.54" y="73.66" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="19"/>
<wire x1="144.78" y1="144.78" x2="160.02" y2="144.78" width="0.1524" layer="91"/>
<label x="147.32" y="144.78" size="1.778" layer="95"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="GND1"/>
<wire x1="-53.34" y1="96.52" x2="-68.58" y2="96.52" width="0.1524" layer="91"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="-68.58" y1="96.52" x2="-68.58" y2="99.06" width="0.1524" layer="91"/>
<label x="-66.04" y="96.52" size="1.778" layer="95"/>
<junction x="-68.58" y="96.52"/>
<wire x1="-68.58" y1="96.52" x2="-68.58" y2="91.44" width="0.1524" layer="91"/>
<pinref part="FRDM1" gate="G$1" pin="GND0"/>
<wire x1="-68.58" y1="91.44" x2="-53.34" y2="91.44" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="160.02" y1="127" x2="160.02" y2="124.46" width="0.1524" layer="91"/>
<pinref part="SV1" gate="1" pin="3"/>
<wire x1="144.78" y1="124.46" x2="160.02" y2="124.46" width="0.1524" layer="91"/>
<label x="152.4" y="124.46" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV2" gate="G$1" pin="6"/>
<wire x1="91.44" y1="88.9" x2="83.82" y2="88.9" width="0.1524" layer="91"/>
<wire x1="83.82" y1="88.9" x2="83.82" y2="91.44" width="0.1524" layer="91"/>
<pinref part="GND3" gate="1" pin="GND"/>
<pinref part="SV2" gate="G$1" pin="16"/>
<wire x1="83.82" y1="91.44" x2="83.82" y2="93.98" width="0.1524" layer="91"/>
<wire x1="83.82" y1="93.98" x2="83.82" y2="96.52" width="0.1524" layer="91"/>
<wire x1="83.82" y1="96.52" x2="83.82" y2="99.06" width="0.1524" layer="91"/>
<wire x1="83.82" y1="99.06" x2="83.82" y2="101.6" width="0.1524" layer="91"/>
<wire x1="83.82" y1="101.6" x2="83.82" y2="104.14" width="0.1524" layer="91"/>
<wire x1="91.44" y1="101.6" x2="83.82" y2="101.6" width="0.1524" layer="91"/>
<junction x="83.82" y="101.6"/>
<pinref part="SV2" gate="G$1" pin="14"/>
<wire x1="91.44" y1="99.06" x2="83.82" y2="99.06" width="0.1524" layer="91"/>
<junction x="83.82" y="99.06"/>
<pinref part="SV2" gate="G$1" pin="12"/>
<wire x1="91.44" y1="96.52" x2="83.82" y2="96.52" width="0.1524" layer="91"/>
<junction x="83.82" y="96.52"/>
<pinref part="SV2" gate="G$1" pin="10"/>
<wire x1="91.44" y1="93.98" x2="83.82" y2="93.98" width="0.1524" layer="91"/>
<junction x="83.82" y="93.98"/>
<pinref part="SV2" gate="G$1" pin="8"/>
<wire x1="91.44" y1="91.44" x2="83.82" y2="91.44" width="0.1524" layer="91"/>
<junction x="83.82" y="91.44"/>
</segment>
<segment>
<pinref part="SV3" gate="G$1" pin="2"/>
<wire x1="147.32" y1="68.58" x2="154.94" y2="68.58" width="0.1524" layer="91"/>
<label x="149.86" y="68.58" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="1"/>
<wire x1="73.66" y1="195.58" x2="63.5" y2="195.58" width="0.1524" layer="91"/>
<label x="66.04" y="195.58" size="1.778" layer="95"/>
<wire x1="63.5" y1="195.58" x2="63.5" y2="203.2" width="0.1524" layer="91"/>
<pinref part="GND4" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="14"/>
<wire x1="88.9" y1="195.58" x2="99.06" y2="195.58" width="0.1524" layer="91"/>
<label x="91.44" y="195.58" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="X1" gate="-2" pin="S"/>
<wire x1="127" y1="165.1" x2="119.38" y2="165.1" width="0.1524" layer="91"/>
<label x="119.38" y="165.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HC-SR04" gate="1" pin="4"/>
<wire x1="86.36" y1="60.96" x2="96.52" y2="60.96" width="0.1524" layer="91"/>
<label x="88.9" y="60.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="GND5" gate="1" pin="GND"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="106.68" y1="45.72" x2="106.68" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="GND"/>
<wire x1="-40.64" y1="185.42" x2="-50.8" y2="185.42" width="0.1524" layer="91"/>
<label x="-50.8" y="185.42" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="QUAD1" gate="1" pin="2"/>
<wire x1="-38.1" y1="165.1" x2="-30.48" y2="165.1" width="0.1524" layer="91"/>
<label x="-38.1" y="165.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV5" gate="1" pin="2"/>
<wire x1="-15.24" y1="165.1" x2="-7.62" y2="165.1" width="0.1524" layer="91"/>
<label x="-15.24" y="165.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV8" gate="G$1" pin="1"/>
<wire x1="-119.38" y1="86.36" x2="-106.68" y2="86.36" width="0.1524" layer="91"/>
<label x="-114.3" y="86.36" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV7" gate="G$1" pin="1"/>
<wire x1="-119.38" y1="101.6" x2="-106.68" y2="101.6" width="0.1524" layer="91"/>
<label x="-114.3" y="101.6" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV6" gate="G$1" pin="1"/>
<wire x1="-119.38" y1="116.84" x2="-106.68" y2="116.84" width="0.1524" layer="91"/>
<label x="-114.3" y="116.84" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV4" gate="G$1" pin="1"/>
<wire x1="-119.38" y1="132.08" x2="-106.68" y2="132.08" width="0.1524" layer="91"/>
<label x="-114.3" y="132.08" size="1.778" layer="95"/>
</segment>
</net>
<net name="RADIO_CS" class="0">
<segment>
<pinref part="SV1" gate="1" pin="23"/>
<wire x1="144.78" y1="149.86" x2="160.02" y2="149.86" width="0.1524" layer="91"/>
<label x="147.32" y="149.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE20"/>
<wire x1="-22.86" y1="73.66" x2="-7.62" y2="73.66" width="0.1524" layer="91"/>
<label x="-17.78" y="73.66" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR1" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="1"/>
<wire x1="106.68" y1="83.82" x2="114.3" y2="83.82" width="0.1524" layer="91"/>
<label x="109.22" y="83.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D5"/>
<wire x1="48.26" y1="73.66" x2="58.42" y2="73.66" width="0.1524" layer="91"/>
<label x="53.34" y="73.66" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR2" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="3"/>
<wire x1="106.68" y1="86.36" x2="114.3" y2="86.36" width="0.1524" layer="91"/>
<label x="109.22" y="86.36" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="A3"/>
<wire x1="-53.34" y1="58.42" x2="-60.96" y2="58.42" width="0.1524" layer="91"/>
<label x="-60.96" y="58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR3" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="5"/>
<wire x1="106.68" y1="88.9" x2="114.3" y2="88.9" width="0.1524" layer="91"/>
<label x="109.22" y="88.9" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D2"/>
<wire x1="48.26" y1="58.42" x2="58.42" y2="58.42" width="0.1524" layer="91"/>
<label x="53.34" y="58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR_LED" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="2"/>
<wire x1="91.44" y1="83.82" x2="83.82" y2="83.82" width="0.1524" layer="91"/>
<label x="81.28" y="83.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D4"/>
<wire x1="48.26" y1="68.58" x2="58.42" y2="68.58" width="0.1524" layer="91"/>
<label x="50.8" y="68.58" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR4" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="7"/>
<wire x1="106.68" y1="91.44" x2="114.3" y2="91.44" width="0.1524" layer="91"/>
<label x="109.22" y="91.44" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D6"/>
<wire x1="48.26" y1="78.74" x2="58.42" y2="78.74" width="0.1524" layer="91"/>
<label x="53.34" y="78.74" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR5" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="9"/>
<wire x1="106.68" y1="93.98" x2="114.3" y2="93.98" width="0.1524" layer="91"/>
<label x="109.22" y="93.98" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D7"/>
<wire x1="48.26" y1="83.82" x2="58.42" y2="83.82" width="0.1524" layer="91"/>
<label x="53.34" y="83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR6" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="11"/>
<wire x1="106.68" y1="96.52" x2="114.3" y2="96.52" width="0.1524" layer="91"/>
<label x="109.22" y="96.52" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D10"/>
<wire x1="48.26" y1="106.68" x2="58.42" y2="106.68" width="0.1524" layer="91"/>
<label x="50.8" y="106.68" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR8" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="15"/>
<wire x1="106.68" y1="101.6" x2="114.3" y2="101.6" width="0.1524" layer="91"/>
<label x="109.22" y="101.6" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="A5"/>
<wire x1="-53.34" y1="48.26" x2="-60.96" y2="48.26" width="0.1524" layer="91"/>
<label x="-60.96" y="48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="IR7" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="13"/>
<wire x1="106.68" y1="99.06" x2="114.3" y2="99.06" width="0.1524" layer="91"/>
<label x="109.22" y="99.06" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="A4"/>
<wire x1="-53.34" y1="53.34" x2="-60.96" y2="53.34" width="0.1524" layer="91"/>
<label x="-60.96" y="53.34" size="1.778" layer="95"/>
</segment>
</net>
<net name="5V" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="5V"/>
<wire x1="-53.34" y1="101.6" x2="-63.5" y2="101.6" width="0.1524" layer="91"/>
<label x="-63.5" y="101.6" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV3" gate="G$1" pin="3"/>
<wire x1="147.32" y1="71.12" x2="154.94" y2="71.12" width="0.1524" layer="91"/>
<label x="149.86" y="71.12" size="1.778" layer="95"/>
</segment>
</net>
<net name="VIN" class="0">
<segment>
<pinref part="SV3" gate="G$1" pin="1"/>
<wire x1="147.32" y1="66.04" x2="154.94" y2="66.04" width="0.1524" layer="91"/>
<label x="149.86" y="66.04" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="13"/>
<wire x1="88.9" y1="193.04" x2="99.06" y2="193.04" width="0.1524" layer="91"/>
<label x="91.44" y="193.04" size="1.778" layer="95"/>
</segment>
</net>
<net name="BOUT2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="12"/>
<wire x1="88.9" y1="190.5" x2="99.06" y2="190.5" width="0.1524" layer="91"/>
<label x="91.44" y="190.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="MOTORL" gate="-2" pin="S"/>
<wire x1="127" y1="182.88" x2="119.38" y2="182.88" width="0.1524" layer="91"/>
<label x="119.38" y="182.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="BOUT1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="11"/>
<wire x1="88.9" y1="187.96" x2="99.06" y2="187.96" width="0.1524" layer="91"/>
<label x="91.44" y="187.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="MOTORL" gate="-1" pin="S"/>
<wire x1="127" y1="187.96" x2="119.38" y2="187.96" width="0.1524" layer="91"/>
<label x="119.38" y="187.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="AOUT2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="10"/>
<wire x1="88.9" y1="185.42" x2="99.06" y2="185.42" width="0.1524" layer="91"/>
<label x="91.44" y="185.42" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="MOTORR" gate="-2" pin="S"/>
<wire x1="127" y1="195.58" x2="119.38" y2="195.58" width="0.1524" layer="91"/>
<label x="119.38" y="195.58" size="1.778" layer="95"/>
</segment>
</net>
<net name="AOUT1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="9"/>
<wire x1="88.9" y1="182.88" x2="99.06" y2="182.88" width="0.1524" layer="91"/>
<label x="91.44" y="182.88" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="MOTORR" gate="-1" pin="S"/>
<wire x1="127" y1="200.66" x2="119.38" y2="200.66" width="0.1524" layer="91"/>
<label x="119.38" y="200.66" size="1.778" layer="95"/>
</segment>
</net>
<net name="DIRR" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="6"/>
<wire x1="73.66" y1="182.88" x2="66.04" y2="182.88" width="0.1524" layer="91"/>
<label x="66.04" y="182.88" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D13"/>
<wire x1="48.26" y1="121.92" x2="58.42" y2="121.92" width="0.1524" layer="91"/>
<label x="50.8" y="121.92" size="1.778" layer="95"/>
</segment>
</net>
<net name="PWMR" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="5"/>
<wire x1="73.66" y1="185.42" x2="66.04" y2="185.42" width="0.1524" layer="91"/>
<label x="66.04" y="185.42" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D11"/>
<wire x1="48.26" y1="111.76" x2="58.42" y2="111.76" width="0.1524" layer="91"/>
<label x="50.8" y="111.76" size="1.778" layer="95"/>
</segment>
</net>
<net name="DIRL" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="4"/>
<wire x1="73.66" y1="187.96" x2="66.04" y2="187.96" width="0.1524" layer="91"/>
<label x="66.04" y="187.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D12"/>
<wire x1="48.26" y1="116.84" x2="58.42" y2="116.84" width="0.1524" layer="91"/>
<label x="50.8" y="116.84" size="1.778" layer="95"/>
</segment>
</net>
<net name="PWML" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="D3"/>
<wire x1="48.26" y1="63.5" x2="55.88" y2="63.5" width="0.1524" layer="91"/>
<label x="53.34" y="63.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="3"/>
<wire x1="73.66" y1="190.5" x2="66.04" y2="190.5" width="0.1524" layer="91"/>
<label x="66.04" y="190.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="BAT" class="0">
<segment>
<pinref part="X1" gate="-1" pin="S"/>
<wire x1="127" y1="170.18" x2="114.3" y2="170.18" width="0.1524" layer="91"/>
<label x="119.38" y="170.18" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="2"/>
</segment>
</net>
<net name="VBAT" class="0">
<segment>
<pinref part="JP1" gate="A" pin="1"/>
<wire x1="91.44" y1="170.18" x2="99.06" y2="170.18" width="0.1524" layer="91"/>
<label x="91.44" y="170.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="VIN"/>
<wire x1="-53.34" y1="86.36" x2="-63.5" y2="86.36" width="0.1524" layer="91"/>
<label x="-63.5" y="86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="TRIG" class="0">
<segment>
<pinref part="HC-SR04" gate="1" pin="2"/>
<wire x1="86.36" y1="55.88" x2="96.52" y2="55.88" width="0.1524" layer="91"/>
<label x="88.9" y="55.88" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="D14"/>
<wire x1="48.26" y1="137.16" x2="58.42" y2="137.16" width="0.1524" layer="91"/>
<label x="50.8" y="137.16" size="1.778" layer="95"/>
</segment>
</net>
<net name="UECHO" class="0">
<segment>
<pinref part="HC-SR04" gate="1" pin="3"/>
<label x="88.9" y="58.42" size="1.778" layer="95"/>
<wire x1="86.36" y1="58.42" x2="106.68" y2="58.42" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="2"/>
<pinref part="R3" gate="G$1" pin="1"/>
<junction x="106.68" y="58.42"/>
</segment>
</net>
<net name="ECHO" class="0">
<segment>
<pinref part="R3" gate="G$1" pin="2"/>
<wire x1="106.68" y1="68.58" x2="106.68" y2="73.66" width="0.1524" layer="91"/>
<wire x1="106.68" y1="73.66" x2="116.84" y2="73.66" width="0.1524" layer="91"/>
<label x="111.76" y="73.66" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="A2"/>
<wire x1="-53.34" y1="63.5" x2="-60.96" y2="63.5" width="0.1524" layer="91"/>
<label x="-60.96" y="63.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="3V3" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="3V3"/>
<wire x1="-40.64" y1="187.96" x2="-50.8" y2="187.96" width="0.1524" layer="91"/>
<label x="-50.8" y="187.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="3V3"/>
<wire x1="-53.34" y1="106.68" x2="-68.58" y2="106.68" width="0.1524" layer="91"/>
<label x="-63.5" y="106.68" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="QUAD1" gate="1" pin="1"/>
<wire x1="-38.1" y1="162.56" x2="-30.48" y2="162.56" width="0.1524" layer="91"/>
<label x="-38.1" y="162.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV5" gate="1" pin="1"/>
<wire x1="-15.24" y1="162.56" x2="-7.62" y2="162.56" width="0.1524" layer="91"/>
<label x="-15.24" y="162.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV7" gate="G$1" pin="2"/>
<wire x1="-119.38" y1="104.14" x2="-106.68" y2="104.14" width="0.1524" layer="91"/>
<label x="-114.3" y="104.14" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV8" gate="G$1" pin="2"/>
<wire x1="-119.38" y1="88.9" x2="-106.68" y2="88.9" width="0.1524" layer="91"/>
<label x="-114.3" y="88.9" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV6" gate="G$1" pin="2"/>
<wire x1="-119.38" y1="119.38" x2="-106.68" y2="119.38" width="0.1524" layer="91"/>
<label x="-114.3" y="119.38" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV4" gate="G$1" pin="2"/>
<wire x1="-119.38" y1="134.62" x2="-106.68" y2="134.62" width="0.1524" layer="91"/>
<label x="-114.3" y="134.62" size="1.778" layer="95"/>
</segment>
</net>
<net name="BTRX" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="RX"/>
<wire x1="-40.64" y1="213.36" x2="-50.8" y2="213.36" width="0.1524" layer="91"/>
<label x="-50.8" y="213.36" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTC4"/>
<wire x1="20.32" y1="63.5" x2="2.54" y2="63.5" width="0.1524" layer="91"/>
<label x="2.54" y="63.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="BTTX" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTC3"/>
<wire x1="20.32" y1="58.42" x2="2.54" y2="58.42" width="0.1524" layer="91"/>
<label x="2.54" y="58.42" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="TX"/>
<wire x1="-40.64" y1="215.9" x2="-50.8" y2="215.9" width="0.1524" layer="91"/>
<label x="-50.8" y="215.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="BTCMD" class="0">
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTC0"/>
<wire x1="20.32" y1="53.34" x2="2.54" y2="53.34" width="0.1524" layer="91"/>
<label x="2.54" y="53.34" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="PIO11"/>
<wire x1="7.62" y1="215.9" x2="17.78" y2="215.9" width="0.1524" layer="91"/>
<label x="12.7" y="215.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="C11" class="0">
<segment>
<pinref part="QUAD1" gate="1" pin="3"/>
<wire x1="-38.1" y1="167.64" x2="-30.48" y2="167.64" width="0.1524" layer="91"/>
<label x="-38.1" y="167.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE2"/>
<wire x1="-22.86" y1="101.6" x2="-12.7" y2="101.6" width="0.1524" layer="91"/>
<label x="-17.78" y="101.6" size="1.778" layer="95"/>
</segment>
</net>
<net name="C12" class="0">
<segment>
<pinref part="QUAD1" gate="1" pin="4"/>
<wire x1="-38.1" y1="170.18" x2="-30.48" y2="170.18" width="0.1524" layer="91"/>
<label x="-38.1" y="170.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE3"/>
<wire x1="-22.86" y1="96.52" x2="-12.7" y2="96.52" width="0.1524" layer="91"/>
<label x="-17.78" y="96.52" size="1.778" layer="95"/>
</segment>
</net>
<net name="C21" class="0">
<segment>
<pinref part="SV5" gate="1" pin="3"/>
<wire x1="-15.24" y1="167.64" x2="-7.62" y2="167.64" width="0.1524" layer="91"/>
<label x="-15.24" y="167.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE4"/>
<wire x1="-22.86" y1="91.44" x2="-12.7" y2="91.44" width="0.1524" layer="91"/>
<label x="-17.78" y="91.44" size="1.778" layer="95"/>
</segment>
</net>
<net name="C22" class="0">
<segment>
<pinref part="SV5" gate="1" pin="4"/>
<wire x1="-15.24" y1="170.18" x2="-7.62" y2="170.18" width="0.1524" layer="91"/>
<label x="-15.24" y="170.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE5"/>
<wire x1="-22.86" y1="86.36" x2="-12.7" y2="86.36" width="0.1524" layer="91"/>
<label x="-17.78" y="86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="10CM2" class="0">
<segment>
<pinref part="SV4" gate="G$1" pin="3"/>
<wire x1="-119.38" y1="137.16" x2="-111.76" y2="137.16" width="0.1524" layer="91"/>
<wire x1="-106.68" y1="137.16" x2="-109.22" y2="137.16" width="0.1524" layer="91"/>
<wire x1="-109.22" y1="137.16" x2="-111.76" y2="137.16" width="0.1524" layer="91"/>
<label x="-114.3" y="137.16" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTC11"/>
<wire x1="20.32" y1="83.82" x2="5.08" y2="83.82" width="0.1524" layer="91"/>
<label x="5.08" y="83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="10CM1" class="0">
<segment>
<pinref part="SV6" gate="G$1" pin="3"/>
<wire x1="-119.38" y1="121.92" x2="-106.68" y2="121.92" width="0.1524" layer="91"/>
<label x="-114.3" y="121.92" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTC10"/>
<wire x1="20.32" y1="78.74" x2="5.08" y2="78.74" width="0.1524" layer="91"/>
<label x="5.08" y="78.74" size="1.778" layer="95"/>
</segment>
</net>
<net name="5CM2" class="0">
<segment>
<pinref part="SV7" gate="G$1" pin="3"/>
<wire x1="-119.38" y1="106.68" x2="-106.68" y2="106.68" width="0.1524" layer="91"/>
<label x="-114.3" y="106.68" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE30"/>
<wire x1="-22.86" y1="48.26" x2="-7.62" y2="48.26" width="0.1524" layer="91"/>
<label x="-12.7" y="48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="5CM1" class="0">
<segment>
<pinref part="SV8" gate="G$1" pin="3"/>
<wire x1="-119.38" y1="91.44" x2="-106.68" y2="91.44" width="0.1524" layer="91"/>
<label x="-114.3" y="91.44" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="FRDM1" gate="G$1" pin="PTE29"/>
<wire x1="-22.86" y1="53.34" x2="-7.62" y2="53.34" width="0.1524" layer="91"/>
<label x="-12.7" y="53.34" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
