<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.05" unitdist="inch" unit="inch" style="lines" multiple="2" display="yes" altdistance="0.025" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
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
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="passive">
<packages>
<package name="C0805-R">
<description>&lt;b&gt;Chip Capacitor 0805 reflow solder&lt;/b&gt;
&lt;p&gt;
Metric Code Size 2012</description>
<wire x1="-0.925" y1="0.6" x2="0.925" y2="0.6" width="0.1016" layer="51"/>
<wire x1="0.925" y1="-0.6" x2="-0.925" y2="-0.6" width="0.1016" layer="51"/>
<smd name="1" x="-1" y="0" dx="1.3" dy="1.5" layer="1"/>
<smd name="2" x="1" y="0" dx="1.3" dy="1.5" layer="1"/>
<text x="0" y="1.25" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.25" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-1" y1="-0.65" x2="-0.5" y2="0.65" layer="51"/>
<rectangle x1="0.5" y1="-0.65" x2="1" y2="0.65" layer="51"/>
</package>
<package name="R0805-R">
<description>&lt;b&gt;Chip Resistor 0805 reflow solder&lt;/b&gt;
&lt;p&gt;
Metric Code Size 2012</description>
<wire x1="-0.925" y1="0.6" x2="0.925" y2="0.6" width="0.1016" layer="51"/>
<wire x1="0.925" y1="-0.6" x2="-0.925" y2="-0.6" width="0.1016" layer="51"/>
<smd name="1" x="-1" y="0" dx="1.3" dy="1.5" layer="1"/>
<smd name="2" x="1" y="0" dx="1.3" dy="1.5" layer="1"/>
<text x="0" y="1.25" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.25" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-1" y1="-0.65" x2="-0.5" y2="0.65" layer="51"/>
<rectangle x1="0.5" y1="-0.65" x2="1" y2="0.65" layer="51"/>
</package>
<package name="C0603-R">
<description>&lt;b&gt;Chip Capacitor 0603 reflow solder&lt;/b&gt;
&lt;p&gt;
Metric Code Size 1608</description>
<text x="0" y="0.75" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.75" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-0.725" y1="0.35" x2="0.725" y2="0.35" width="0.1016" layer="51"/>
<wire x1="0.725" y1="-0.35" x2="-0.725" y2="-0.35" width="0.1016" layer="51"/>
<smd name="1" x="-0.75" y="0" dx="1" dy="1" layer="1"/>
<smd name="2" x="0.75" y="0" dx="1" dy="1" layer="1"/>
<rectangle x1="-0.8" y1="-0.4" x2="-0.45" y2="0.4" layer="51"/>
<rectangle x1="0.45" y1="-0.4" x2="0.8" y2="0.4" layer="51"/>
</package>
<package name="R0603-R">
<description>&lt;b&gt;Chip Resistor 0603 reflow solder&lt;/b&gt;
&lt;p&gt;
Metric Code Size 1608</description>
<text x="0" y="0.75" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.75" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-0.725" y1="0.35" x2="0.725" y2="0.35" width="0.1016" layer="51"/>
<wire x1="0.725" y1="-0.35" x2="-0.725" y2="-0.35" width="0.1016" layer="51"/>
<smd name="1" x="-0.75" y="0" dx="1" dy="1" layer="1"/>
<smd name="2" x="0.75" y="0" dx="1" dy="1" layer="1"/>
<rectangle x1="-0.8" y1="-0.4" x2="-0.45" y2="0.4" layer="51"/>
<rectangle x1="0.45" y1="-0.4" x2="0.8" y2="0.4" layer="51"/>
</package>
<package name="C1206-R">
<description>&lt;b&gt;Ceramic Chip Capacitor 1206 reflow solder&lt;/b&gt;&lt;p&gt;
Metric Code Size 3216</description>
<wire x1="-1.525" y1="0.75" x2="1.525" y2="0.75" width="0.1016" layer="51"/>
<wire x1="1.525" y1="-0.75" x2="-1.525" y2="-0.75" width="0.1016" layer="51"/>
<smd name="1" x="-1.5" y="0" dx="1.5" dy="2" layer="1"/>
<smd name="2" x="1.5" y="0" dx="1.5" dy="2" layer="1"/>
<text x="0" y="1.125" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.125" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-1.6" y1="-0.8" x2="-1.1" y2="0.8" layer="51"/>
<rectangle x1="1.1" y1="-0.8" x2="1.6" y2="0.8" layer="51"/>
</package>
<package name="C1210-R">
<description>&lt;b&gt;Ceramic Chip Capacitor 1210 reflow solder&lt;/b&gt;&lt;p&gt;
Metric Code Size 3225</description>
<wire x1="-1.525" y1="1.175" x2="1.525" y2="1.175" width="0.1016" layer="51"/>
<wire x1="1.525" y1="-1.175" x2="-1.525" y2="-1.175" width="0.1016" layer="51"/>
<smd name="1" x="-1.5" y="0" dx="1.5" dy="2.9" layer="1"/>
<smd name="2" x="1.5" y="0" dx="1.5" dy="2.9" layer="1"/>
<text x="0" y="1.625" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.625" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-1.6" y1="-1.25" x2="-1.1" y2="1.25" layer="51"/>
<rectangle x1="1.1" y1="-1.25" x2="1.6" y2="1.25" layer="51"/>
</package>
<package name="LRMA-2512&lt;R003">
<description>&lt;b&gt;LRMA 2512 R003&lt;/b&gt;
&lt;p&gt;
TT Electronics Low Resistance Metal Alloy Resistor</description>
<smd name="2" x="2.2" y="0" dx="4" dy="3.1" layer="1" rot="R90"/>
<smd name="1" x="-2.2" y="0" dx="4" dy="3.1" layer="1" rot="R90"/>
<rectangle x1="-3.25" y1="-1.6" x2="-1.25" y2="1.6" layer="51"/>
<wire x1="-1.25" y1="1.45" x2="1.15" y2="1.45" width="0.3" layer="51"/>
<rectangle x1="1.25" y1="-1.6" x2="3.25" y2="1.6" layer="51"/>
<rectangle x1="1.15" y1="-1.6" x2="3.15" y2="1.6" layer="51"/>
<wire x1="-1.25" y1="-1.45" x2="1.15" y2="-1.45" width="0.3" layer="51"/>
<text x="0" y="2.25" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-3.25" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
</package>
<package name="IFSC-1515AH-01">
<description>&lt;b&gt;Vishay IFSC-1515AH-01&lt;/b&gt;
&lt;p&gt;
Low Profile, High Current Inductors
&lt;p&gt;

Datasheet:
&lt;a href="http://www.vishay.com/docs/34295/sc15ah01.pdf"&gt;http://www.vishay.com/docs/34295/sc15ah01.pdf&lt;/a&gt;

&lt;p&gt;
Mouser: 
&lt;a href="http://ch.mouser.com/Search/Refine.aspx?Keyword=IFSC-1515AH-01"&gt;http://ch.mouser.com/Search/Refine.aspx?Keyword=IFSC-1515AH-01&lt;/a&gt;</description>
<smd name="1" x="0" y="-1.4" dx="1.4" dy="3.8" layer="1" rot="R270"/>
<smd name="2" x="0" y="1.4" dx="1.4" dy="3.8" layer="1" rot="R270"/>
<wire x1="-1.646" y1="1.8" x2="1.646" y2="1.8" width="0.1016" layer="51"/>
<wire x1="1.646" y1="1.8" x2="1.9" y2="1.546" width="0.1016" layer="51" curve="-90"/>
<wire x1="1.9" y1="1.546" x2="1.9" y2="-1.546" width="0.1016" layer="51"/>
<wire x1="1.9" y1="-1.546" x2="1.646" y2="-1.8" width="0.1016" layer="51" curve="-90"/>
<wire x1="1.646" y1="-1.8" x2="-1.646" y2="-1.8" width="0.1016" layer="51"/>
<wire x1="-1.646" y1="-1.8" x2="-1.9" y2="-1.546" width="0.1016" layer="51" curve="-90"/>
<wire x1="-1.9" y1="-1.546" x2="-1.9" y2="1.546" width="0.1016" layer="51"/>
<wire x1="-1.9" y1="1.546" x2="-1.646" y2="1.8" width="0.1016" layer="51" curve="-90"/>
<wire x1="-1.6" y1="1.5" x2="1.6" y2="1.5" width="0.1016" layer="51"/>
<wire x1="1.6" y1="1.5" x2="1.6" y2="-1.5" width="0.1016" layer="51"/>
<wire x1="1.6" y1="-1.5" x2="-1.6" y2="-1.5" width="0.1016" layer="51"/>
<wire x1="-1.6" y1="-1.5" x2="-1.6" y2="1.5" width="0.1016" layer="51"/>
<text x="0" y="2.5" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-3.5" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-1.9" y1="-0.4" x2="-1.9" y2="0.4" width="0.1016" layer="21"/>
<wire x1="1.9" y1="-0.4" x2="1.9" y2="0.4" width="0.1016" layer="21"/>
<rectangle x1="-1.85" y1="1.75" x2="1.85" y2="2.05" layer="51"/>
<rectangle x1="-1.85" y1="-2.05" x2="1.85" y2="-1.75" layer="51"/>
</package>
<package name="PM124SH">
<description>PM124SH Series - Shielded SMD Power Inductors</description>
<smd name="1" x="-3.2" y="0" dx="2.9" dy="5.4" layer="1" rot="R180"/>
<smd name="2" x="3.2" y="0" dx="2.9" dy="5.4" layer="1" rot="R180"/>
<wire x1="-5.4" y1="6.4" x2="5.4" y2="6.4" width="0.1" layer="21"/>
<wire x1="-5.4" y1="-6.4" x2="5.4" y2="-6.4" width="0.1" layer="21"/>
<wire x1="6.4" y1="-5.4" x2="6.4" y2="5.4" width="0.1" layer="21"/>
<circle x="0" y="0" radius="4.75" width="0.1" layer="51"/>
<wire x1="-6.4" y1="-5.4" x2="-6.4" y2="5.4" width="0.1" layer="21"/>
<wire x1="-4.6231625" y1="2.5018375" x2="-2.501840625" y2="4.623159375" width="0.1" layer="51" curve="-180"/>
<wire x1="2.5018375" y1="4.6231625" x2="4.623159375" y2="2.501840625" width="0.1" layer="51" curve="-180"/>
<wire x1="-2.5018375" y1="-4.6231625" x2="-4.623159375" y2="-2.501840625" width="0.1" layer="51" curve="-180"/>
<wire x1="4.6231625" y1="-2.5018375" x2="2.501840625" y2="-4.623159375" width="0.1" layer="51" curve="-180"/>
<wire x1="-2.5" y1="4.625" x2="2.5" y2="4.625" width="0.1" layer="51" curve="-56.786039"/>
<wire x1="2.5" y1="-4.625" x2="-2.5" y2="-4.625" width="0.1" layer="51" curve="-56.786039"/>
<wire x1="4.625" y1="2.5" x2="4.625" y2="-2.5" width="0.1" layer="51" curve="-56.786039"/>
<wire x1="-4.625" y1="-2.5" x2="-4.625" y2="2.5" width="0.1" layer="51" curve="-56.786039"/>
<wire x1="-6.4" y1="5.4" x2="-5.4" y2="6.4" width="0.1" layer="21" curve="-90"/>
<wire x1="5.4" y1="6.4" x2="6.4" y2="5.4" width="0.1" layer="21" curve="-90"/>
<wire x1="-5.4" y1="-6.4" x2="-6.4" y2="-5.4" width="0.1" layer="21" curve="-90"/>
<wire x1="6.4" y1="-5.4" x2="5.4" y2="-6.4" width="0.1" layer="21" curve="-90"/>
<text x="0" y="6.75" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-7.75" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
</package>
<package name="NR8040-SERIES">
<smd name="1" x="0" y="2.8" dx="1.8" dy="7.5" layer="1" rot="R270"/>
<smd name="2" x="0" y="-2.8" dx="1.8" dy="7.5" layer="1" rot="R270"/>
<wire x1="-3.25" y1="4" x2="3.25" y2="4" width="0.1" layer="51"/>
<wire x1="3.25" y1="4" x2="3.25" y2="3.5" width="0.1" layer="51"/>
<wire x1="3.25" y1="3.5" x2="3.25" y2="2.75" width="0.1" layer="51"/>
<wire x1="3.25" y1="-2.5" x2="3.25" y2="-3.5" width="0.1" layer="51"/>
<wire x1="3.25" y1="-3.5" x2="3.25" y2="-4" width="0.1" layer="51"/>
<wire x1="-3.25" y1="4" x2="-3.25" y2="3.5" width="0.1" layer="51"/>
<wire x1="-3.25" y1="3.5" x2="-3.25" y2="2.75" width="0.1" layer="51"/>
<wire x1="-3.25" y1="-2.75" x2="-3.25" y2="-3.5" width="0.1" layer="51"/>
<wire x1="-3.25" y1="-3.5" x2="-3.25" y2="-4" width="0.1" layer="51"/>
<wire x1="-3.25" y1="-4" x2="3.25" y2="-4" width="0.1" layer="51"/>
<wire x1="-4" y1="-2" x2="-4" y2="2" width="0.1" layer="21"/>
<wire x1="-4" y1="2" x2="-3.25" y2="2.75" width="0.1" layer="51"/>
<wire x1="-4" y1="-2" x2="-3.25" y2="-2.75" width="0.1" layer="51"/>
<wire x1="4" y1="2" x2="4" y2="-1.75" width="0.1" layer="21"/>
<wire x1="4" y1="-1.75" x2="3.25" y2="-2.5" width="0.1" layer="51"/>
<wire x1="4" y1="2" x2="3.25" y2="2.75" width="0.1" layer="51"/>
<wire x1="-3.25" y1="3.5" x2="3.25" y2="3.5" width="0.1" layer="51"/>
<wire x1="-3.25" y1="-3.5" x2="3.25" y2="-3.5" width="0.1" layer="51"/>
<text x="0" y="4.25" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-5.25" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
</package>
<package name="SRU1048-SERIES">
<description>&lt;b&gt;BOURNS SRU1048 Series&lt;/b&gt;</description>
<smd name="1" x="-4.5" y="0" dx="1.8" dy="3.6" layer="1"/>
<text x="0" y="1" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<smd name="2" x="4.5" y="0" dx="1.8" dy="3.6" layer="1"/>
<wire x1="-2.25" y1="5" x2="2.25" y2="5" width="0.1" layer="51"/>
<wire x1="2.25" y1="-5" x2="5" y2="-2.25" width="0.1" layer="51"/>
<wire x1="5" y1="2.25" x2="2.25" y2="5" width="0.1" layer="51"/>
<wire x1="-5" y1="-2.25" x2="-2.25" y2="-5" width="0.1" layer="51"/>
<wire x1="-5" y1="2.25" x2="-2.25" y2="5" width="0.1" layer="51"/>
<circle x="0" y="0" radius="4.279309375" width="0.25" layer="51"/>
<wire x1="-5" y1="-2.25" x2="-5" y2="2.25" width="0.1" layer="51"/>
<wire x1="-2.25" y1="-5" x2="2.25" y2="-5" width="0.1" layer="51"/>
<wire x1="5" y1="2.25" x2="5" y2="-2.25" width="0.1" layer="51"/>
</package>
<package name="SRU5028-SERIES">
<description>&lt;b&gt;Bourns SRU5028 Series - Shielded SMD Power Inductors&lt;/b&gt;</description>
<smd name="NC2" x="-2.4" y="0" dx="1.1" dy="2" layer="1"/>
<smd name="NC1" x="2.4" y="0" dx="1.1" dy="2" layer="1"/>
<smd name="L2" x="0" y="2.4" dx="1.1" dy="2" layer="1" rot="R90"/>
<smd name="L1" x="0" y="-2.4" dx="1.1" dy="2" layer="1" rot="R90"/>
<wire x1="-2.7" y1="1.1" x2="-2.7" y2="-1.1" width="0.1" layer="51"/>
<wire x1="2.7" y1="1.1" x2="2.7" y2="-1.1" width="0.1" layer="51"/>
<wire x1="-1.1" y1="2.7" x2="1.1" y2="2.7" width="0.1" layer="51"/>
<circle x="0" y="0" radius="2" width="0.1" layer="51"/>
<wire x1="-1.1" y1="-2.7" x2="1.1" y2="-2.7" width="0.1" layer="51"/>
<wire x1="0" y1="-1.5" x2="0" y2="-1.95" width="0.2" layer="51"/>
<wire x1="0" y1="1.5" x2="0" y2="1.95" width="0.2" layer="51"/>
<circle x="0" y="1" radius="0.05" width="0.2" layer="21"/>
<wire x1="1.2" y1="-2.6" x2="2.6" y2="-1.2" width="0.1" layer="21"/>
<text x="0" y="3.25" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-0.5" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="1.1" y1="-2.7" x2="1.2" y2="-2.6" width="0.1" layer="51"/>
<wire x1="2.6" y1="-1.2" x2="2.7" y2="-1.1" width="0.1" layer="51"/>
<wire x1="2.6" y1="1.2" x2="1.2" y2="2.6" width="0.1" layer="21"/>
<wire x1="2.7" y1="1.1" x2="2.6" y2="1.2" width="0.1" layer="51"/>
<wire x1="1.2" y1="2.6" x2="1.1" y2="2.7" width="0.1" layer="51"/>
<wire x1="-1.2" y1="2.6" x2="-2.6" y2="1.2" width="0.1" layer="21"/>
<wire x1="-1.1" y1="2.7" x2="-1.2" y2="2.6" width="0.1" layer="51"/>
<wire x1="-2.6" y1="1.2" x2="-2.7" y2="1.1" width="0.1" layer="51"/>
<wire x1="-2.6" y1="-1.2" x2="-1.2" y2="-2.6" width="0.1" layer="21"/>
<wire x1="-2.7" y1="-1.1" x2="-2.6" y2="-1.2" width="0.1" layer="51"/>
<wire x1="-1.2" y1="-2.6" x2="-1.1" y2="-2.7" width="0.1" layer="51"/>
</package>
<package name="SRU1048-SERIES_WITHOUT_CREAM-MASK">
<description>&lt;b&gt;BOURNS SRU1048 Series&lt;/b&gt;
&lt;p&gt;
Bestückungsvariante indem die Spule 90° gedreht wird</description>
<smd name="1" x="-4.5" y="0" dx="1.8" dy="3.6" layer="1" cream="no"/>
<text x="0" y="1" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<smd name="2" x="4.5" y="0" dx="1.8" dy="3.6" layer="1" cream="no"/>
<wire x1="-2.25" y1="5" x2="2.25" y2="5" width="0.1" layer="51"/>
<wire x1="2.25" y1="-5" x2="5" y2="-2.25" width="0.1" layer="51"/>
<wire x1="5" y1="2.25" x2="2.25" y2="5" width="0.1" layer="51"/>
<wire x1="-5" y1="-2.25" x2="-2.25" y2="-5" width="0.1" layer="51"/>
<wire x1="-5" y1="2.25" x2="-2.25" y2="5" width="0.1" layer="51"/>
<circle x="0" y="0" radius="4.279309375" width="0.25" layer="51"/>
<wire x1="-5" y1="-2.25" x2="-5" y2="2.25" width="0.1" layer="51"/>
<wire x1="-2.25" y1="-5" x2="2.25" y2="-5" width="0.1" layer="51"/>
<wire x1="5" y1="2.25" x2="5" y2="-2.25" width="0.1" layer="51"/>
</package>
<package name="L0603-R">
<text x="0" y="0.75" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.75" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-0.725" y1="0.35" x2="0.725" y2="0.35" width="0.1016" layer="51"/>
<wire x1="0.725" y1="-0.35" x2="-0.725" y2="-0.35" width="0.1016" layer="51"/>
<smd name="1" x="-0.75" y="0" dx="1" dy="1" layer="1"/>
<smd name="2" x="0.75" y="0" dx="1" dy="1" layer="1"/>
<rectangle x1="-0.8" y1="-0.4" x2="-0.45" y2="0.4" layer="51"/>
<rectangle x1="0.45" y1="-0.4" x2="0.8" y2="0.4" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="C">
<wire x1="0" y1="2.54" x2="0" y2="0.762" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-0.762" width="0.1524" layer="94"/>
<text x="1.27" y="1.27" size="1.778" layer="95">&gt;NAME</text>
<text x="1.27" y="-3.048" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.032" y1="-0.762" x2="2.032" y2="-0.254" layer="94"/>
<rectangle x1="-2.032" y1="0.254" x2="2.032" y2="0.762" layer="94"/>
<pin name="1" x="0" y="2.54" visible="off" length="point" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-2.54" visible="off" length="point" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="R">
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<text x="0" y="1.4986" size="1.778" layer="95" align="bottom-center">&gt;NAME</text>
<text x="0" y="-3.302" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="L">
<text x="0" y="1.4986" size="1.778" layer="95" align="bottom-center">&gt;NAME</text>
<text x="0" y="-3.302" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-1.016" y1="-3.556" x2="1.016" y2="3.556" layer="94" rot="R90"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="C" prefix="C" uservalue="yes">
<description>&lt;B&gt;Capacitor&lt;/B&gt;</description>
<gates>
<gate name="G$1" symbol="C" x="0" y="0"/>
</gates>
<devices>
<device name="0603" package="C0603-R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="C0805-R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="C1206-R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1210" package="C1210-R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="R" prefix="R" uservalue="yes">
<description>&lt;B&gt;Resistor&lt;/B&gt;</description>
<gates>
<gate name="G$1" symbol="R" x="0" y="0"/>
</gates>
<devices>
<device name="0805" package="R0805-R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="R0603-R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LRMA-2512-3.1" package="LRMA-2512&lt;R003">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="L" prefix="L" uservalue="yes">
<description>&lt;b&gt;Inductor&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="L" x="0" y="0"/>
</gates>
<devices>
<device name="-IFSC-1515AH-01" package="IFSC-1515AH-01">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-PM124SH-SERIES" package="PM124SH">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-NR8040" package="NR8040-SERIES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-SRU1048-SERIES" package="SRU1048-SERIES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-SRU5028-SERIES" package="SRU5028-SERIES">
<connects>
<connect gate="G$1" pin="1" pad="L1"/>
<connect gate="G$1" pin="2" pad="L2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-SRU1048-SERIES_WITHOUT_CREAM-MASK" package="SRU1048-SERIES_WITHOUT_CREAM-MASK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="" package="L0603-R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="connectors">
<packages>
<package name="USB-MINI-B-VERTICAL_AMPHENOL">
<pad name="3" x="1.3" y="0" drill="0.6" diameter="1.2"/>
<pad name="5" x="1.3" y="1.6" drill="0.6" diameter="1.2"/>
<pad name="1" x="1.3" y="-1.6" drill="0.6" diameter="1.2"/>
<pad name="4" x="-1.3" y="0.8" drill="0.6" diameter="1.2"/>
<pad name="2" x="-1.3" y="-0.8" drill="0.6" diameter="1.2"/>
<wire x1="-1.746" y1="3.9" x2="-0.105209375" y2="3.9" width="0.127" layer="51"/>
<wire x1="-0.105209375" y1="3.9" x2="0.07439375" y2="3.82560625" width="0.127" layer="51" curve="-44.999502"/>
<wire x1="0.07439375" y1="3.82560625" x2="0.32560625" y2="3.57439375" width="0.127" layer="51"/>
<wire x1="0.32560625" y1="3.57439375" x2="0.505209375" y2="3.5" width="0.127" layer="51" curve="44.999295"/>
<wire x1="0.505209375" y1="3.5" x2="1.746" y2="3.5" width="0.127" layer="51"/>
<wire x1="-1.746" y1="3.9" x2="-2" y2="3.646" width="0.127" layer="51" curve="90"/>
<wire x1="-2" y1="3.646" x2="-2" y2="-3.646" width="0.127" layer="51"/>
<wire x1="-2" y1="-3.646" x2="-1.746" y2="-3.9" width="0.127" layer="51" curve="90"/>
<wire x1="-1.746" y1="-3.9" x2="-0.105209375" y2="-3.9" width="0.127" layer="51"/>
<wire x1="-0.105209375" y1="-3.9" x2="0.07439375" y2="-3.82560625" width="0.127" layer="51" curve="44.999502"/>
<wire x1="0.07439375" y1="-3.82560625" x2="0.32560625" y2="-3.57439375" width="0.127" layer="51"/>
<wire x1="0.32560625" y1="-3.57439375" x2="0.505209375" y2="-3.5" width="0.127" layer="51" curve="-44.999295"/>
<wire x1="0.505209375" y1="-3.5" x2="1.746" y2="-3.5" width="0.127" layer="51"/>
<wire x1="1.746" y1="3.5" x2="2" y2="3.246" width="0.127" layer="51" curve="-90"/>
<wire x1="1.746" y1="-3.5" x2="2" y2="-3.246" width="0.127" layer="51" curve="90"/>
<wire x1="2" y1="-3.246" x2="2" y2="3.246" width="0.127" layer="51"/>
<text x="0" y="5" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-6.25" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-2" y1="-3.9" x2="2" y2="3.9" layer="39"/>
<pad name="P$3" x="0.05" y="-3.65" drill="0.6" diameter="2" shape="long"/>
<pad name="P$4" x="0" y="3.65" drill="0.6" diameter="2" shape="long"/>
<wire x1="-1.275" y1="3.65" x2="1.275" y2="3.65" width="1" layer="46"/>
<wire x1="-1.275" y1="-3.65" x2="1.275" y2="-3.65" width="1" layer="46"/>
</package>
<package name="USB-MINI-B-VERTICAL_WUERTH">
<description>&lt;b&gt;Würth MINI-USB, TYP-B VERT &lt;/b&gt;
&lt;p&gt;
VERTICAL MINI USB TYPE B 5 CONTACTS  

&lt;p&gt;
Mouser: 
&lt;a href="http://ch.mouser.com/Search/Refine.aspx?Keyword=710-651005136421 "&gt;http://ch.mouser.com/Search/Refine.aspx?Keyword=710-651005136421 &lt;/a&gt;</description>
<pad name="S1" x="0" y="4.2" drill="2" shape="square"/>
<pad name="S2" x="0" y="-4.2" drill="2" shape="square"/>
<pad name="3" x="0.9" y="0" drill="0.6"/>
<pad name="5" x="0.9" y="1.6" drill="0.6"/>
<pad name="1" x="0.9" y="-1.6" drill="0.6"/>
<pad name="4" x="-0.9" y="0.8" drill="0.6"/>
<pad name="2" x="-0.9" y="-0.8" drill="0.6"/>
<wire x1="-2" y1="-3.9" x2="-2" y2="3.9" width="0.127" layer="21"/>
<wire x1="2" y1="-3.9" x2="2" y2="3.9" width="0.127" layer="21"/>
<wire x1="-1.746" y1="3.9" x2="-0.105209375" y2="3.9" width="0.127" layer="51"/>
<wire x1="-0.105209375" y1="3.9" x2="0.07439375" y2="3.82560625" width="0.127" layer="51" curve="-44.999502"/>
<wire x1="0.07439375" y1="3.82560625" x2="0.32560625" y2="3.57439375" width="0.127" layer="51"/>
<wire x1="0.32560625" y1="3.57439375" x2="0.505209375" y2="3.5" width="0.127" layer="51" curve="44.999295"/>
<wire x1="0.505209375" y1="3.5" x2="1.746" y2="3.5" width="0.127" layer="51"/>
<wire x1="-1.746" y1="3.9" x2="-2" y2="3.646" width="0.127" layer="51" curve="90"/>
<wire x1="-2" y1="3.646" x2="-2" y2="-3.646" width="0.127" layer="51"/>
<wire x1="-2" y1="-3.646" x2="-1.746" y2="-3.9" width="0.127" layer="51" curve="90"/>
<wire x1="-1.746" y1="-3.9" x2="-0.105209375" y2="-3.9" width="0.127" layer="51"/>
<wire x1="-0.105209375" y1="-3.9" x2="0.07439375" y2="-3.82560625" width="0.127" layer="51" curve="44.999502"/>
<wire x1="0.07439375" y1="-3.82560625" x2="0.32560625" y2="-3.57439375" width="0.127" layer="51"/>
<wire x1="0.32560625" y1="-3.57439375" x2="0.505209375" y2="-3.5" width="0.127" layer="51" curve="-44.999295"/>
<wire x1="0.505209375" y1="-3.5" x2="1.746" y2="-3.5" width="0.127" layer="51"/>
<wire x1="1.746" y1="3.5" x2="2" y2="3.246" width="0.127" layer="51" curve="-90"/>
<wire x1="1.746" y1="-3.5" x2="2" y2="-3.246" width="0.127" layer="51" curve="90"/>
<wire x1="2" y1="-3.246" x2="2" y2="3.246" width="0.127" layer="51"/>
<text x="0" y="6" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-7" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-2" y1="-3.9" x2="2" y2="3.9" layer="39"/>
</package>
<package name="STIFTLEISTE_2X5_1.27_SMD">
<description>&lt;b&gt;Stiftleiste 2x5 Pin, Raster: 1.27&lt;/b&gt;
&lt;br&gt;
z.B. HARWIN M50-360xx42</description>
<smd name="2" x="-2.54" y="1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="1" x="-2.54" y="-1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="4" x="-1.27" y="1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="3" x="-1.27" y="-1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="6" x="0" y="1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="5" x="0" y="-1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="8" x="1.27" y="1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="7" x="1.27" y="-1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="10" x="2.54" y="1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<smd name="9" x="2.54" y="-1.95" dx="2.4" dy="0.74" layer="1" rot="R90"/>
<wire x1="-3.25" y1="2.75" x2="-3.25" y2="-2.75" width="0.127" layer="21"/>
<wire x1="3.25" y1="2.75" x2="3.25" y2="-2.75" width="0.127" layer="21"/>
<text x="0" y="3.5" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-4.5" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-2.794" y1="1.016" x2="-2.286" y2="2.921" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="2.921" layer="51"/>
<rectangle x1="-0.254" y1="1.016" x2="0.254" y2="2.921" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="2.921" layer="51"/>
<rectangle x1="2.286" y1="1.016" x2="2.794" y2="2.921" layer="51"/>
<rectangle x1="2.286" y1="-2.921" x2="2.794" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-2.921" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="-0.254" y1="-2.921" x2="0.254" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="-2.921" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="-2.794" y1="-2.921" x2="-2.286" y2="-1.016" layer="51"/>
</package>
<package name="STIFTLEISTE_2X5_1.27_TH">
<description>&lt;b&gt;Stiftleiste 2x5 Pin, Raster: 1.27&lt;/b&gt;
&lt;br&gt;
z.B. HARWIN M50-350xx42</description>
<pad name="2" x="-2.54" y="0.635" drill="0.7" diameter="1" shape="offset" rot="R90"/>
<pad name="4" x="-1.27" y="0.635" drill="0.7" diameter="1" shape="offset" rot="R90"/>
<pad name="1" x="-2.54" y="-0.635" drill="0.7" diameter="1" shape="offset" rot="R270"/>
<pad name="3" x="-1.27" y="-0.635" drill="0.7" diameter="1" shape="offset" rot="R270"/>
<pad name="6" x="0" y="0.635" drill="0.7" diameter="1" shape="offset" rot="R90"/>
<pad name="5" x="0" y="-0.635" drill="0.7" diameter="1" shape="offset" rot="R270"/>
<pad name="8" x="1.27" y="0.635" drill="0.7" diameter="1" shape="offset" rot="R90"/>
<pad name="7" x="1.27" y="-0.635" drill="0.7" diameter="1" shape="offset" rot="R270"/>
<pad name="10" x="2.54" y="0.635" drill="0.7" diameter="1" shape="offset" rot="R90"/>
<pad name="9" x="2.54" y="-0.635" drill="0.7" diameter="1" shape="offset" rot="R270"/>
<text x="0" y="2.5" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-3.5" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-3.25" y1="1.7" x2="-3.25" y2="-1.7" width="0.127" layer="21"/>
<wire x1="3.25" y1="1.7" x2="3.25" y2="-1.7" width="0.127" layer="21"/>
</package>
<package name="USB-MINI-B-HORIZ_HIROSE-UX60SC-MB-5ST">
<smd name="3" x="0" y="6.1" dx="1.4" dy="0.5" layer="1" rot="R90"/>
<smd name="4" x="0.8" y="6.1" dx="1.4" dy="0.5" layer="1" rot="R90"/>
<smd name="2" x="-0.8" y="6.1" dx="1.4" dy="0.5" layer="1" rot="R90"/>
<smd name="5" x="1.6" y="6.1" dx="1.4" dy="0.5" layer="1" rot="R90"/>
<smd name="1" x="-1.6" y="6.1" dx="1.4" dy="0.5" layer="1" rot="R90"/>
<smd name="S1" x="-4.2" y="3.6" dx="2.5" dy="3.8" layer="1"/>
<smd name="S2" x="4.2" y="3.6" dx="2.5" dy="3.8" layer="1"/>
<wire x1="-3.8" y1="0" x2="3.8" y2="0" width="0.1" layer="51"/>
<wire x1="-3.8" y1="0" x2="-3.8" y2="2.25" width="0.1" layer="51"/>
<wire x1="-3.8" y1="2.25" x2="-5" y2="2.25" width="0.1" layer="51"/>
<wire x1="-5" y1="2.25" x2="-5" y2="3.25" width="0.1" layer="51"/>
<wire x1="-5" y1="3.25" x2="-3.8" y2="3.25" width="0.1" layer="51"/>
<wire x1="-3.8" y1="3.25" x2="-3.8" y2="4" width="0.1" layer="51"/>
<wire x1="-3.8" y1="4" x2="-5" y2="4" width="0.1" layer="51"/>
<wire x1="-5" y1="4" x2="-5" y2="5" width="0.1" layer="51"/>
<wire x1="-5" y1="5" x2="-3.8" y2="5" width="0.1" layer="51"/>
<wire x1="-3.8" y1="5" x2="-3.8" y2="6.25" width="0.1" layer="51"/>
<wire x1="-3.8" y1="6.25" x2="-2" y2="6.25" width="0.1" layer="51"/>
<wire x1="-2" y1="6.25" x2="-2" y2="6.5" width="0.1" layer="51"/>
<wire x1="-2" y1="6.5" x2="2" y2="6.5" width="0.1" layer="51"/>
<wire x1="2" y1="6.5" x2="2" y2="6.25" width="0.1" layer="51"/>
<wire x1="2" y1="6.25" x2="3.8" y2="6.25" width="0.1" layer="51"/>
<wire x1="3.8" y1="6.25" x2="3.8" y2="5" width="0.1" layer="51"/>
<wire x1="3.8" y1="5" x2="5" y2="5" width="0.1" layer="51"/>
<wire x1="5" y1="5" x2="5" y2="4" width="0.1" layer="51"/>
<wire x1="5" y1="4" x2="3.8" y2="4" width="0.1" layer="51"/>
<wire x1="3.8" y1="4" x2="3.8" y2="3.25" width="0.1" layer="51"/>
<wire x1="3.8" y1="3.25" x2="5" y2="3.25" width="0.1" layer="51"/>
<wire x1="5" y1="3.25" x2="5" y2="2.25" width="0.1" layer="51"/>
<wire x1="5" y1="2.25" x2="3.8" y2="2.25" width="0.1" layer="51"/>
<wire x1="3.8" y1="2.25" x2="3.8" y2="0" width="0.1" layer="51"/>
<polygon width="0.1" layer="41">
<vertex x="-3" y="0"/>
<vertex x="3" y="0"/>
<vertex x="3" y="0.5"/>
<vertex x="1.5" y="0.5"/>
<vertex x="1.5" y="1.25"/>
<vertex x="2.75" y="1.25"/>
<vertex x="2.75" y="2"/>
<vertex x="1.5" y="2"/>
<vertex x="1.5" y="3.6"/>
<vertex x="-1.5" y="3.6"/>
<vertex x="-1.5" y="2"/>
<vertex x="-2.75" y="2"/>
<vertex x="-2.75" y="1.25"/>
<vertex x="-1.5" y="1.25"/>
<vertex x="-1.5" y="0.5"/>
<vertex x="-3" y="0.5"/>
</polygon>
<wire x1="-3.8" y1="0" x2="-3.8" y2="-0.5" width="0.1" layer="51"/>
<wire x1="-3.8" y1="-0.5" x2="3.8" y2="-0.5" width="0.1" layer="51"/>
<wire x1="3.8" y1="0" x2="3.8" y2="-0.5" width="0.1" layer="51"/>
<text x="0" y="4" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="2.5" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
</package>
<package name="SOLDERPAD_TH_0.9">
<pad name="1" x="0" y="0" drill="0.9" diameter="1.5"/>
</package>
<package name="USB-A-MOLEX_48037">
<hole x="-2.25" y="2.75" drill="1.1"/>
<hole x="2.25" y="2.75" drill="1.1"/>
<smd name="3" x="-1" y="5.35" dx="1.2" dy="2" layer="1" rot="R180"/>
<smd name="2" x="1" y="5.35" dx="1.2" dy="2" layer="1" rot="R180"/>
<smd name="1" x="3.5" y="5.35" dx="1.2" dy="2" layer="1" rot="R180"/>
<smd name="4" x="-3.5" y="5.35" dx="1.2" dy="2" layer="1" rot="R180"/>
<pad name="S1A" x="-5.85" y="4" drill="1" shape="offset" rot="R270"/>
<wire x1="-5.85" y1="1.5" x2="-5.85" y2="4" width="1" layer="46"/>
<wire x1="-6.9" y1="0" x2="6.8" y2="0" width="0.127" layer="21"/>
<pad name="S1B" x="-5.85" y="1.5" drill="1" shape="offset" rot="R90"/>
<pad name="S2A" x="5.85" y="4" drill="1" shape="offset" rot="R270"/>
<wire x1="5.85" y1="1.5" x2="5.85" y2="4" width="1" layer="46"/>
<pad name="S2B" x="5.85" y="1.5" drill="1" shape="offset" rot="R90"/>
</package>
<package name="SD-105027-001">
<description>&lt;B&gt;Molex Micro-SD Card holder&lt;/B&gt;
&lt;p&gt;
SD-105027-001</description>
<smd name="P1" x="3.85" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="P2" x="2.75" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="P3" x="1.65" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="P4" x="0.9" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="G1" x="0.2" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="P5" x="-0.55" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="P6" x="-1.65" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="P7" x="-2.75" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="P8" x="-3.85" y="-3.93" dx="1" dy="0.5" layer="1" rot="R90"/>
<smd name="C4" x="-5.225" y="2.13" dx="1.2" dy="1.05" layer="1" rot="R90"/>
<smd name="C1" x="-5.225" y="-2.32" dx="1.2" dy="1.05" layer="1" rot="R90"/>
<smd name="C2" x="5.225" y="-2.32" dx="1.2" dy="1.05" layer="1" rot="R90"/>
<smd name="C3" x="5.225" y="2.13" dx="1.2" dy="1.05" layer="1" rot="R90"/>
<wire x1="5.62" y1="2.73" x2="5.62" y2="1.23" width="0.1" layer="51"/>
<wire x1="-4.5" y1="-4.27" x2="-5.62" y2="-4.27" width="0.1" layer="21"/>
<wire x1="-5.62" y1="-4.27" x2="-5.62" y2="-3.27" width="0.1" layer="21"/>
<wire x1="-5.62" y1="1.23" x2="-5.62" y2="2.73" width="0.1" layer="51"/>
<wire x1="-4.5" y1="2.73" x2="4.5" y2="2.73" width="0.1" layer="21"/>
<wire x1="-5.62" y1="2.73" x2="-4.5" y2="2.73" width="0.1" layer="51"/>
<wire x1="4.5" y1="2.73" x2="5.62" y2="2.73" width="0.1" layer="51"/>
<wire x1="-5.62" y1="-1.52" x2="-5.62" y2="1.23" width="0.1" layer="21"/>
<wire x1="5.62" y1="-1.52" x2="5.62" y2="1.23" width="0.1" layer="21"/>
<wire x1="-5.62" y1="-3.27" x2="-5.62" y2="-1.52" width="0.1" layer="51"/>
<wire x1="5.62" y1="-3.27" x2="5.62" y2="-1.52" width="0.1" layer="51"/>
<wire x1="4.5" y1="-4.27" x2="-4.5" y2="-4.27" width="0.1" layer="51"/>
<wire x1="4.5" y1="-4.27" x2="5.62" y2="-4.27" width="0.1" layer="21"/>
<wire x1="5.62" y1="-4.27" x2="5.62" y2="-3.27" width="0.1" layer="21"/>
<wire x1="-5" y1="-4.27" x2="-5" y2="-11.52" width="0.1" layer="51"/>
<wire x1="-5" y1="-11.52" x2="-4" y2="-12.52" width="0.1" layer="51" curve="90"/>
<wire x1="-4" y1="-12.52" x2="5.5" y2="-12.52" width="0.1" layer="51"/>
<wire x1="5.5" y1="-12.52" x2="6.5" y2="-11.52" width="0.1" layer="51" curve="90"/>
<wire x1="6.5" y1="-11.52" x2="6.5" y2="-8.27" width="0.1" layer="51"/>
<wire x1="6.5" y1="-5.77" x2="6.5" y2="-4.15" width="0.1" layer="51"/>
<wire x1="6.5" y1="-4.15" x2="5.62" y2="-3.27" width="0.1" layer="51"/>
<wire x1="6.5" y1="-5.77" x2="5.8" y2="-5.77" width="0.1" layer="51"/>
<wire x1="5.8" y1="-5.77" x2="5.6" y2="-5.97" width="0.1" layer="51" curve="90"/>
<wire x1="5.6" y1="-5.97" x2="5.6" y2="-7.37" width="0.1" layer="51"/>
<wire x1="5.6" y1="-7.37" x2="6.5" y2="-8.27" width="0.1" layer="51"/>
<text x="-2.5" y="-9.27" size="1" layer="51">Micro SD</text>
</package>
</packages>
<symbols>
<symbol name="MINI-USB-5">
<wire x1="-2.54" y1="6.35" x2="-2.54" y2="-6.35" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-6.35" x2="-1.27" y2="-7.62" width="0.254" layer="94" curve="90"/>
<wire x1="-1.27" y1="-7.62" x2="0" y2="-7.62" width="0.254" layer="94"/>
<wire x1="0" y1="-7.62" x2="1.016" y2="-8.128" width="0.254" layer="94" curve="-53.130102"/>
<wire x1="1.016" y1="-8.128" x2="2.54" y2="-8.89" width="0.254" layer="94" curve="53.130102"/>
<wire x1="2.54" y1="-8.89" x2="5.08" y2="-8.89" width="0.254" layer="94"/>
<wire x1="5.08" y1="-8.89" x2="6.35" y2="-7.62" width="0.254" layer="94" curve="90"/>
<wire x1="6.35" y1="-7.62" x2="6.35" y2="7.62" width="0.254" layer="94"/>
<wire x1="-2.54" y1="6.35" x2="-1.27" y2="7.62" width="0.254" layer="94" curve="-90"/>
<wire x1="-1.27" y1="7.62" x2="0" y2="7.62" width="0.254" layer="94"/>
<wire x1="0" y1="7.62" x2="1.016" y2="8.128" width="0.254" layer="94" curve="53.130102"/>
<wire x1="1.016" y1="8.128" x2="2.54" y2="8.89" width="0.254" layer="94" curve="-53.130102"/>
<wire x1="2.54" y1="8.89" x2="5.08" y2="8.89" width="0.254" layer="94"/>
<wire x1="5.08" y1="8.89" x2="6.35" y2="7.62" width="0.254" layer="94" curve="-90"/>
<wire x1="0" y1="5.08" x2="0" y2="-5.08" width="0.254" layer="94"/>
<wire x1="0" y1="-5.08" x2="1.27" y2="-6.35" width="0.254" layer="94"/>
<wire x1="1.27" y1="-6.35" x2="3.81" y2="-6.35" width="0.254" layer="94"/>
<wire x1="3.81" y1="-6.35" x2="3.81" y2="6.35" width="0.254" layer="94"/>
<wire x1="3.81" y1="6.35" x2="1.27" y2="6.35" width="0.254" layer="94"/>
<wire x1="1.27" y1="6.35" x2="0" y2="5.08" width="0.254" layer="94"/>
<text x="-2.54" y="11.43" size="1.778" layer="95" font="vector">&gt;PART</text>
<text x="10.16" y="-7.62" size="1.778" layer="96" font="vector" rot="R90">&gt;VALUE</text>
<pin name="1" x="-5.08" y="5.08" visible="pin" direction="pas"/>
<pin name="2" x="-5.08" y="2.54" visible="pin" direction="pas"/>
<pin name="3" x="-5.08" y="0" visible="pin" direction="pas"/>
<pin name="4" x="-5.08" y="-2.54" visible="pin" direction="pas"/>
<pin name="5" x="-5.08" y="-5.08" visible="pin" direction="pas"/>
<text x="-1.27" y="5.08" size="1.143" layer="94" align="bottom-center">5V</text>
<text x="-1.27" y="2.54" size="1.143" layer="94" align="bottom-center">D-</text>
<text x="-1.27" y="0" size="1.143" layer="94" align="bottom-center">D+</text>
<text x="-1.27" y="-2.54" size="1.143" layer="94" align="bottom-center">ID</text>
<text x="-1.27" y="-5.08" size="1.143" layer="94" align="bottom-center">G</text>
</symbol>
<symbol name="SHIELD_2">
<wire x1="2.54" y1="0" x2="5.08" y2="0" width="0.254" layer="94" style="shortdash"/>
<wire x1="5.08" y1="0" x2="7.62" y2="2.54" width="0.254" layer="94" style="shortdash" curve="90"/>
<wire x1="7.62" y1="2.54" x2="7.62" y2="17.78" width="0.254" layer="94" style="shortdash"/>
<wire x1="7.62" y1="17.78" x2="5.08" y2="20.32" width="0.254" layer="94" style="shortdash" curve="90"/>
<text x="7.62" y="-2.54" size="1.778" layer="95" font="vector">&gt;NAME</text>
<pin name="S1" x="2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="S2" x="5.08" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<wire x1="2.54" y1="20.32" x2="5.08" y2="20.32" width="0.254" layer="94" style="shortdash"/>
</symbol>
<symbol name="10-PIN_DUAL">
<wire x1="-2.54" y1="-3.556" x2="-2.54" y2="-4.064" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-4.064" x2="-1.016" y2="-4.064" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-4.064" x2="-1.016" y2="-3.556" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-3.556" x2="-2.54" y2="-3.556" width="0.254" layer="94"/>
<text x="-3.175" y="9.906" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.175" y="-11.811" size="1.778" layer="96">&gt;VALUE</text>
<pin name="3" x="-5.08" y="3.81" visible="off" length="short" direction="pas"/>
<wire x1="-2.54" y1="0.254" x2="-2.54" y2="-0.254" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.254" x2="-1.016" y2="-0.254" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-0.254" x2="-1.016" y2="0.254" width="0.254" layer="94"/>
<wire x1="-1.016" y1="0.254" x2="-2.54" y2="0.254" width="0.254" layer="94"/>
<pin name="1" x="-5.08" y="7.62" visible="off" length="short" direction="pas"/>
<wire x1="-2.54" y1="-7.366" x2="-2.54" y2="-7.874" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-7.874" x2="-1.016" y2="-7.874" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-7.874" x2="-1.016" y2="-7.366" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-7.366" x2="-2.54" y2="-7.366" width="0.254" layer="94"/>
<pin name="5" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
<wire x1="2.54" y1="-4.064" x2="2.54" y2="-3.556" width="0.254" layer="94"/>
<wire x1="2.54" y1="-3.556" x2="1.016" y2="-3.556" width="0.254" layer="94"/>
<wire x1="1.016" y1="-3.556" x2="1.016" y2="-4.064" width="0.254" layer="94"/>
<wire x1="1.016" y1="-4.064" x2="2.54" y2="-4.064" width="0.254" layer="94"/>
<pin name="4" x="5.08" y="3.81" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="2.54" y1="-0.254" x2="2.54" y2="0.254" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.254" x2="1.016" y2="0.254" width="0.254" layer="94"/>
<wire x1="1.016" y1="0.254" x2="1.016" y2="-0.254" width="0.254" layer="94"/>
<wire x1="1.016" y1="-0.254" x2="2.54" y2="-0.254" width="0.254" layer="94"/>
<pin name="2" x="5.08" y="7.62" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="2.54" y1="-7.874" x2="2.54" y2="-7.366" width="0.254" layer="94"/>
<wire x1="2.54" y1="-7.366" x2="1.016" y2="-7.366" width="0.254" layer="94"/>
<wire x1="1.016" y1="-7.366" x2="1.016" y2="-7.874" width="0.254" layer="94"/>
<wire x1="1.016" y1="-7.874" x2="2.54" y2="-7.874" width="0.254" layer="94"/>
<pin name="6" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="3.175" y1="9.525" x2="3.175" y2="-9.525" width="0.254" layer="94"/>
<wire x1="3.175" y1="-9.525" x2="-3.175" y2="-9.525" width="0.254" layer="94"/>
<wire x1="-3.175" y1="-9.525" x2="-3.175" y2="9.525" width="0.254" layer="94"/>
<text x="-4.699" y="0.254" size="1.524" layer="95">5</text>
<text x="-4.572" y="-3.556" size="1.524" layer="95">7</text>
<text x="3.556" y="0.254" size="1.524" layer="95">6</text>
<text x="3.556" y="-3.556" size="1.524" layer="95">8</text>
<text x="3.556" y="-7.366" size="1.524" layer="95">10</text>
<text x="-4.699" y="-7.366" size="1.524" layer="95">9</text>
<wire x1="-2.54" y1="4.064" x2="-2.54" y2="3.556" width="0.254" layer="94"/>
<wire x1="-2.54" y1="3.556" x2="-1.016" y2="3.556" width="0.254" layer="94"/>
<wire x1="-1.016" y1="3.556" x2="-1.016" y2="4.064" width="0.254" layer="94"/>
<wire x1="-1.016" y1="4.064" x2="-2.54" y2="4.064" width="0.254" layer="94"/>
<pin name="7" x="-5.08" y="-3.81" visible="off" length="short" direction="pas"/>
<wire x1="-2.54" y1="7.874" x2="-2.54" y2="7.366" width="0.254" layer="94"/>
<wire x1="-2.54" y1="7.366" x2="-1.016" y2="7.366" width="0.254" layer="94"/>
<wire x1="-1.016" y1="7.366" x2="-1.016" y2="7.874" width="0.254" layer="94"/>
<wire x1="-1.016" y1="7.874" x2="-2.54" y2="7.874" width="0.254" layer="94"/>
<pin name="8" x="5.08" y="-3.81" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="2.54" y1="3.556" x2="2.54" y2="4.064" width="0.254" layer="94"/>
<wire x1="2.54" y1="4.064" x2="1.016" y2="4.064" width="0.254" layer="94"/>
<wire x1="1.016" y1="4.064" x2="1.016" y2="3.556" width="0.254" layer="94"/>
<wire x1="1.016" y1="3.556" x2="2.54" y2="3.556" width="0.254" layer="94"/>
<pin name="9" x="-5.08" y="-7.62" visible="off" length="short" direction="pas"/>
<wire x1="2.54" y1="7.366" x2="2.54" y2="7.874" width="0.254" layer="94"/>
<wire x1="2.54" y1="7.874" x2="1.016" y2="7.874" width="0.254" layer="94"/>
<wire x1="1.016" y1="7.874" x2="1.016" y2="7.366" width="0.254" layer="94"/>
<wire x1="1.016" y1="7.366" x2="2.54" y2="7.366" width="0.254" layer="94"/>
<pin name="10" x="5.08" y="-7.62" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="-3.175" y1="9.525" x2="3.175" y2="9.525" width="0.254" layer="94"/>
<text x="-4.699" y="7.874" size="1.524" layer="95">1</text>
<text x="-4.572" y="4.064" size="1.524" layer="95">3</text>
<text x="3.556" y="7.874" size="1.524" layer="95">2</text>
<text x="3.556" y="4.064" size="1.524" layer="95">4</text>
</symbol>
<symbol name="SOLDERPAD">
<text x="2.54" y="0" size="1.778" layer="96" align="center-left">&gt;NAME</text>
<pin name="PAD" x="-2.54" y="0" visible="off" length="short"/>
<circle x="0.762" y="0" radius="0.762" width="0.254" layer="94"/>
</symbol>
<symbol name="USB">
<wire x1="-0.635" y1="5.588" x2="-2.159" y2="5.588" width="0.254" layer="94"/>
<wire x1="-2.159" y1="5.588" x2="-2.159" y2="5.08" width="0.254" layer="94"/>
<wire x1="-2.159" y1="5.08" x2="-2.159" y2="4.572" width="0.254" layer="94"/>
<wire x1="-2.159" y1="4.572" x2="-0.635" y2="4.572" width="0.254" layer="94"/>
<wire x1="-0.635" y1="3.048" x2="-2.159" y2="3.048" width="0.254" layer="94"/>
<wire x1="-2.159" y1="3.048" x2="-2.159" y2="2.54" width="0.254" layer="94"/>
<wire x1="-2.159" y1="2.54" x2="-2.159" y2="2.032" width="0.254" layer="94"/>
<wire x1="-2.159" y1="2.032" x2="-0.635" y2="2.032" width="0.254" layer="94"/>
<wire x1="-0.635" y1="0.508" x2="-2.159" y2="0.508" width="0.254" layer="94"/>
<wire x1="-2.159" y1="0.508" x2="-2.159" y2="0" width="0.254" layer="94"/>
<wire x1="-2.159" y1="0" x2="-2.159" y2="-0.508" width="0.254" layer="94"/>
<wire x1="-2.159" y1="-0.508" x2="-0.635" y2="-0.508" width="0.254" layer="94"/>
<wire x1="-0.635" y1="-2.032" x2="-2.159" y2="-2.032" width="0.254" layer="94"/>
<wire x1="-2.159" y1="-2.032" x2="-2.159" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-2.159" y1="-2.54" x2="-2.159" y2="-3.048" width="0.254" layer="94"/>
<wire x1="-2.159" y1="-3.048" x2="-0.635" y2="-3.048" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-1.905" y2="-5.08" width="0.127" layer="94"/>
<wire x1="-1.524" y1="-5.08" x2="-0.762" y2="-5.08" width="0.127" layer="94"/>
<wire x1="-0.254" y1="-5.08" x2="0.508" y2="-5.08" width="0.127" layer="94"/>
<wire x1="0.508" y1="-5.08" x2="0.508" y2="-4.572" width="0.127" layer="94"/>
<wire x1="0.508" y1="4.826" x2="0.508" y2="5.334" width="0.127" layer="94"/>
<wire x1="0.508" y1="5.842" x2="0.508" y2="6.35" width="0.127" layer="94"/>
<wire x1="0.508" y1="6.35" x2="0" y2="6.35" width="0.127" layer="94"/>
<wire x1="-0.635" y1="6.35" x2="-1.27" y2="6.35" width="0.127" layer="94"/>
<wire x1="-1.905" y1="6.35" x2="-2.54" y2="6.35" width="0.127" layer="94"/>
<wire x1="-2.54" y1="6.35" x2="-2.54" y2="5.588" width="0.127" layer="94"/>
<wire x1="-2.54" y1="4.572" x2="-2.54" y2="3.048" width="0.127" layer="94"/>
<wire x1="-2.54" y1="2.032" x2="-2.54" y2="0.508" width="0.127" layer="94"/>
<wire x1="-2.54" y1="-0.508" x2="-2.54" y2="-2.032" width="0.127" layer="94"/>
<wire x1="-2.54" y1="-3.048" x2="-2.54" y2="-5.08" width="0.127" layer="94"/>
<wire x1="2.032" y1="-2.413" x2="4.572" y2="-2.413" width="0.1998" layer="94"/>
<wire x1="4.572" y1="-2.413" x2="4.572" y2="-1.778" width="0.1998" layer="94"/>
<wire x1="4.572" y1="-1.778" x2="4.953" y2="-1.778" width="0.1998" layer="94"/>
<wire x1="4.953" y1="-1.778" x2="4.953" y2="2.032" width="0.1998" layer="94"/>
<wire x1="4.953" y1="2.032" x2="4.572" y2="2.032" width="0.1998" layer="94"/>
<wire x1="4.572" y1="2.032" x2="4.572" y2="2.794" width="0.1998" layer="94"/>
<wire x1="4.572" y1="2.794" x2="2.032" y2="2.794" width="0.1998" layer="94"/>
<wire x1="0.508" y1="3.556" x2="0.508" y2="4.064" width="0.127" layer="94"/>
<wire x1="0.508" y1="2.286" x2="0.508" y2="2.794" width="0.127" layer="94"/>
<wire x1="0.508" y1="1.016" x2="0.508" y2="1.524" width="0.127" layer="94"/>
<wire x1="0.508" y1="-0.254" x2="0.508" y2="0.254" width="0.127" layer="94"/>
<wire x1="0.508" y1="-1.524" x2="0.508" y2="-1.016" width="0.127" layer="94"/>
<wire x1="0.508" y1="-2.794" x2="0.508" y2="-2.286" width="0.127" layer="94"/>
<wire x1="0.508" y1="-4.064" x2="0.508" y2="-3.556" width="0.127" layer="94"/>
<wire x1="2.032" y1="2.794" x2="2.032" y2="2.032" width="0.1998" layer="94"/>
<wire x1="2.032" y1="2.032" x2="1.651" y2="2.032" width="0.1998" layer="94"/>
<wire x1="1.651" y1="2.032" x2="1.651" y2="-1.778" width="0.1998" layer="94"/>
<wire x1="1.651" y1="-1.778" x2="2.032" y2="-1.778" width="0.1998" layer="94"/>
<wire x1="2.032" y1="-1.778" x2="2.032" y2="-2.413" width="0.1998" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-2.159" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.159" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-2.159" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.159" y2="5.08" width="0.1524" layer="94"/>
<text x="1.27" y="5.588" size="1.778" layer="95">&gt;NAME</text>
<text x="1.27" y="-5.842" size="1.778" layer="96">&gt;VALUE</text>
<text x="3.937" y="-1.397" size="1.27" layer="94" font="vector" rot="R90">USB</text>
<pin name="1" x="-5.08" y="5.08" visible="pad" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="-5.08" y="2.54" visible="pad" length="short" direction="pas" swaplevel="1"/>
<pin name="3" x="-5.08" y="0" visible="pad" length="short" direction="pas" swaplevel="1"/>
<pin name="4" x="-5.08" y="-2.54" visible="pad" length="short" direction="pas" swaplevel="1"/>
<pin name="S2" x="0" y="-7.62" visible="off" length="short" direction="pas" swaplevel="2" rot="R90"/>
<pin name="S1" x="-2.54" y="-7.62" visible="off" length="short" direction="pas" swaplevel="2" rot="R90"/>
</symbol>
<symbol name="MICRO-SD-SWITCH">
<wire x1="-10.16" y1="12.7" x2="-10.16" y2="10.16" width="0.254" layer="94"/>
<wire x1="-10.16" y1="10.16" x2="-10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="7.62" x2="-10.16" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-12.7" x2="15.24" y2="-12.7" width="0.254" layer="94"/>
<wire x1="15.24" y1="-12.7" x2="15.24" y2="12.7" width="0.254" layer="94"/>
<wire x1="15.24" y1="12.7" x2="-10.16" y2="12.7" width="0.254" layer="94"/>
<text x="-10.16" y="13.335" size="1.778" layer="95" font="vector">&gt;NAME</text>
<text x="-10.16" y="-15.24" size="1.778" layer="96" font="vector">&gt;VALUE</text>
<text x="11.43" y="3.81" size="1.27" layer="94" rot="R270" align="center-left">MicroSD
Card</text>
<pin name="DAT2_(X)" x="-12.7" y="-5.08" visible="pin" length="short" direction="pas"/>
<pin name="CD/DAT3_(CS)" x="-12.7" y="-7.62" visible="pin" length="short" direction="pas"/>
<pin name="VDD" x="-12.7" y="10.16" visible="pin" length="short" direction="pas"/>
<pin name="VSS" x="-12.7" y="-10.16" visible="pin" length="short" direction="pas"/>
<pin name="CLK_(SCLK)" x="-12.7" y="2.54" visible="pin" length="short" direction="pas"/>
<pin name="CMD_(MOSI)" x="-12.7" y="5.08" visible="pin" length="short" direction="pas"/>
<pin name="DAT0_(MISO)" x="-12.7" y="0" visible="pin" length="short" direction="pas"/>
<pin name="DAT1_(X)" x="-12.7" y="-2.54" visible="pin" length="short" direction="pas"/>
<wire x1="8.89" y1="5.08" x2="8.89" y2="3.175" width="0.1524" layer="94"/>
<wire x1="8.89" y1="3.175" x2="7.62" y2="1.905" width="0.1524" layer="94"/>
<wire x1="7.62" y1="1.905" x2="7.62" y2="1.27" width="0.1524" layer="94"/>
<wire x1="7.62" y1="1.27" x2="8.255" y2="1.27" width="0.1524" layer="94"/>
<wire x1="8.255" y1="1.27" x2="8.255" y2="0" width="0.1524" layer="94"/>
<wire x1="8.255" y1="0" x2="7.62" y2="-0.635" width="0.1524" layer="94"/>
<wire x1="7.62" y1="-0.635" x2="7.62" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="7.62" y1="-5.08" x2="13.97" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="8.89" y1="5.08" x2="13.335" y2="5.08" width="0.1524" layer="94"/>
<wire x1="13.335" y1="5.08" x2="13.97" y2="4.445" width="0.1524" layer="94"/>
<wire x1="13.97" y1="4.445" x2="13.97" y2="-5.08" width="0.1524" layer="94"/>
<pin name="SWITCH" x="-12.7" y="7.62" visible="pin" length="short" direction="pas"/>
<wire x1="-10.16" y1="10.16" x2="-9.525" y2="10.16" width="0.127" layer="94"/>
<wire x1="-9.525" y1="10.16" x2="-9.525" y2="9.525" width="0.127" layer="94"/>
<wire x1="-9.525" y1="9.525" x2="-8.636" y2="8.636" width="0.127" layer="94"/>
<wire x1="-10.16" y1="7.62" x2="-9.525" y2="7.62" width="0.127" layer="94"/>
<wire x1="-9.525" y1="7.62" x2="-9.525" y2="8.255" width="0.127" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MINI-USB-SHIELD" prefix="X">
<description>&lt;b&gt;MINI USB-B Conector&lt;/b&gt;&lt;p&gt;</description>
<gates>
<gate name="G" symbol="MINI-USB-5" x="0" y="0" addlevel="must"/>
<gate name="S" symbol="SHIELD_2" x="0" y="-10.16" addlevel="always"/>
</gates>
<devices>
<device name="-WUERTH" package="USB-MINI-B-VERTICAL_WUERTH">
<connects>
<connect gate="G" pin="1" pad="1"/>
<connect gate="G" pin="2" pad="2"/>
<connect gate="G" pin="3" pad="3"/>
<connect gate="G" pin="4" pad="4"/>
<connect gate="G" pin="5" pad="5"/>
<connect gate="S" pin="S1" pad="S1"/>
<connect gate="S" pin="S2" pad="S2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MFR" value="Würth Electronics" constant="no"/>
<attribute name="MFR_PART-NO" value="651005136421" constant="no"/>
<attribute name="MOUSER_PART-NO" value="710-651005136421" constant="no"/>
</technology>
</technologies>
</device>
<device name="-AMPHENOL" package="USB-MINI-B-VERTICAL_AMPHENOL">
<connects>
<connect gate="G" pin="1" pad="1"/>
<connect gate="G" pin="2" pad="2"/>
<connect gate="G" pin="3" pad="3"/>
<connect gate="G" pin="4" pad="4"/>
<connect gate="G" pin="5" pad="5"/>
<connect gate="S" pin="S1" pad="P$3"/>
<connect gate="S" pin="S2" pad="P$4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MFR" value="Amphenol Commercial Products" constant="no"/>
<attribute name="MFR_PART-NO" value="UE25BE5510H" constant="no"/>
<attribute name="MOUSER_PART-NO" value="523-UE25BE5510H" constant="no"/>
</technology>
</technologies>
</device>
<device name="HIROSE-UX60SC-MB-5ST" package="USB-MINI-B-HORIZ_HIROSE-UX60SC-MB-5ST">
<connects>
<connect gate="G" pin="1" pad="1"/>
<connect gate="G" pin="2" pad="2"/>
<connect gate="G" pin="3" pad="3"/>
<connect gate="G" pin="4" pad="4"/>
<connect gate="G" pin="5" pad="5"/>
<connect gate="S" pin="S1" pad="S1"/>
<connect gate="S" pin="S2" pad="S2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MFR" value="HIROSE" constant="no"/>
<attribute name="MFR_PART-NO" value="UX60SC-MB-5ST" constant="no"/>
<attribute name="MOUSER_PART-NO" value="798-UX60SCMB5ST01" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="STIFTLEISTE_2X5_1.27" prefix="X">
<gates>
<gate name="G$1" symbol="10-PIN_DUAL" x="-2.54" y="0"/>
</gates>
<devices>
<device name="-SMD" package="STIFTLEISTE_2X5_1.27_SMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
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
<device name="-TH" package="STIFTLEISTE_2X5_1.27_TH">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
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
<deviceset name="SOLDERPAD" prefix="P">
<gates>
<gate name="G$1" symbol="SOLDERPAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOLDERPAD_TH_0.9">
<connects>
<connect gate="G$1" pin="PAD" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USB-A">
<gates>
<gate name="G$1" symbol="USB" x="0" y="0"/>
</gates>
<devices>
<device name="MOLEX_48037" package="USB-A-MOLEX_48037">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="S1" pad="S1A S1B"/>
<connect gate="G$1" pin="S2" pad="S2A S2B"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MOLEX-MICRO-SD" prefix="X">
<description>&lt;B&gt;Molex Micro-SD Card holder&lt;/B&gt;
&lt;p&gt;
SD-105027-001</description>
<gates>
<gate name="G$1" symbol="MICRO-SD-SWITCH" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SD-105027-001">
<connects>
<connect gate="G$1" pin="CD/DAT3_(CS)" pad="P2"/>
<connect gate="G$1" pin="CLK_(SCLK)" pad="P5"/>
<connect gate="G$1" pin="CMD_(MOSI)" pad="P3"/>
<connect gate="G$1" pin="DAT0_(MISO)" pad="P7"/>
<connect gate="G$1" pin="DAT1_(X)" pad="P8"/>
<connect gate="G$1" pin="DAT2_(X)" pad="P1"/>
<connect gate="G$1" pin="SWITCH" pad="G1"/>
<connect gate="G$1" pin="VDD" pad="P4"/>
<connect gate="G$1" pin="VSS" pad="P6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="discreteSemiconductors">
<packages>
<package name="CSTCE">
<smd name="2" x="0" y="0" dx="2" dy="0.4" layer="1" rot="R90"/>
<smd name="3" x="1.2" y="0" dx="2" dy="0.4" layer="1" rot="R90"/>
<smd name="1" x="-1.2" y="0" dx="2" dy="0.4" layer="1" rot="R90"/>
<wire x1="-1.8" y1="0.65" x2="1.8" y2="0.65" width="0.1" layer="51"/>
<wire x1="-1.8" y1="-0.65" x2="1.8" y2="-0.65" width="0.1" layer="51"/>
<wire x1="-1.8" y1="0.65" x2="-1.8" y2="-0.65" width="0.1" layer="21"/>
<wire x1="1.8" y1="0.65" x2="1.8" y2="-0.65" width="0.1" layer="21"/>
<wire x1="-1.8" y1="0.65" x2="-1.65" y2="0.65" width="0.1" layer="21"/>
<wire x1="-1.8" y1="-0.65" x2="-1.65" y2="-0.65" width="0.1" layer="21"/>
<wire x1="-0.75" y1="0.65" x2="-0.45" y2="0.65" width="0.1" layer="21"/>
<wire x1="-0.75" y1="-0.65" x2="-0.45" y2="-0.65" width="0.1" layer="21"/>
<wire x1="0.45" y1="0.65" x2="0.75" y2="0.65" width="0.1" layer="21"/>
<wire x1="0.45" y1="-0.65" x2="0.75" y2="-0.65" width="0.1" layer="21"/>
<wire x1="1.8" y1="-0.65" x2="1.65" y2="-0.65" width="0.1" layer="21"/>
<wire x1="1.8" y1="0.65" x2="1.65" y2="0.65" width="0.1" layer="21"/>
<text x="0" y="1.25" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.25" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
</package>
<package name="SOT-23">
<description>&lt;b&gt;SOT23 Reflow soldering&lt;/b&gt;</description>
<wire x1="1.5" y1="0.65" x2="1.5" y2="-0.65" width="0.2" layer="51"/>
<wire x1="1.5" y1="-0.65" x2="-1.5" y2="-0.65" width="0.2" layer="51"/>
<wire x1="-1.5" y1="-0.65" x2="-1.5" y2="0.65" width="0.2" layer="51"/>
<wire x1="-1.5" y1="0.65" x2="1.5" y2="0.65" width="0.2" layer="51"/>
<wire x1="-1.5" y1="-0.25" x2="-1.5" y2="0.65" width="0.2" layer="21"/>
<wire x1="-1.5" y1="0.65" x2="-0.7" y2="0.65" width="0.2" layer="21"/>
<wire x1="1.5" y1="0.65" x2="1.5" y2="-0.25" width="0.2" layer="21"/>
<wire x1="0.7" y1="0.65" x2="1.5" y2="0.65" width="0.2" layer="21"/>
<wire x1="-0.25" y1="-0.65" x2="0.25" y2="-0.65" width="0.2" layer="21"/>
<smd name="3" x="0" y="1" dx="0.8" dy="0.9" layer="1"/>
<smd name="2" x="0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<smd name="1" x="-0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<text x="0" y="2" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-3" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-0.225" y1="0.7" x2="0.225" y2="1.3" layer="51"/>
<rectangle x1="0.725" y1="-1.3" x2="1.175" y2="-0.7" layer="51"/>
<rectangle x1="-1.175" y1="-1.3" x2="-0.7112" y2="-0.7" layer="51"/>
</package>
<package name="SOT-323">
<smd name="3" x="0" y="0.95" dx="0.6" dy="0.55" layer="1"/>
<smd name="2" x="0.65" y="-0.95" dx="0.6" dy="0.55" layer="1"/>
<smd name="1" x="-0.65" y="-0.95" dx="0.6" dy="0.55" layer="1"/>
<text x="0" y="1.5" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.5" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="1" y1="0.45" x2="1" y2="-0.45" width="0.15" layer="51"/>
<wire x1="1" y1="-0.45" x2="-1" y2="-0.45" width="0.1524" layer="51"/>
<wire x1="-1" y1="-0.45" x2="-1" y2="0.45" width="0.1524" layer="51"/>
<wire x1="-1" y1="0.45" x2="1" y2="0.45" width="0.1524" layer="51"/>
<wire x1="1" y1="0.45" x2="1" y2="-0.45" width="0.15" layer="21"/>
<wire x1="1" y1="-0.45" x2="-1" y2="-0.45" width="0.15" layer="21"/>
<wire x1="-1" y1="-0.45" x2="-1" y2="0.45" width="0.15" layer="21"/>
<wire x1="-1" y1="0.45" x2="1" y2="0.45" width="0.15" layer="21"/>
<rectangle x1="-0.8" y1="-1.1" x2="-0.5" y2="-0.5" layer="51"/>
<rectangle x1="0.5" y1="-1.1" x2="0.8" y2="-0.5" layer="51"/>
<rectangle x1="-0.15" y1="0.5" x2="0.15" y2="1.1" layer="51"/>
</package>
<package name="D0603-R">
<text x="0" y="1" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-0.725" y1="0.35" x2="0.725" y2="0.35" width="0.1016" layer="51"/>
<smd name="1" x="-0.75" y="0" dx="1" dy="1" layer="1"/>
<smd name="2" x="0.75" y="0" dx="1" dy="1" layer="1"/>
<rectangle x1="-0.8" y1="-0.4" x2="-0.45" y2="0.4" layer="51"/>
<rectangle x1="0.45" y1="-0.4" x2="0.8" y2="0.4" layer="51"/>
<wire x1="0.725" y1="-0.35" x2="-0.725" y2="-0.35" width="0.1016" layer="51"/>
<wire x1="-0.15" y1="0.2" x2="-0.15" y2="-0.2" width="0.05" layer="51"/>
<wire x1="-0.15" y1="-0.2" x2="0.15" y2="0" width="0.05" layer="51"/>
<wire x1="0.15" y1="0" x2="-0.15" y2="0.2" width="0.05" layer="51"/>
<wire x1="0.15" y1="0.2" x2="0.15" y2="0" width="0.05" layer="51"/>
<wire x1="0.15" y1="0" x2="0.15" y2="-0.2" width="0.05" layer="51"/>
</package>
<package name="CRYSTAL-AB38T">
<pad name="1" x="-0.55" y="0" drill="0.4" diameter="0.9"/>
<pad name="2" x="0.55" y="0" drill="0.4" diameter="0.9"/>
<wire x1="-1.6" y1="3" x2="-1.6" y2="11.3" width="0.1" layer="21"/>
<wire x1="-1.6" y1="11.3" x2="1.6" y2="11.3" width="0.1" layer="21"/>
<wire x1="1.6" y1="11.3" x2="1.6" y2="3" width="0.1" layer="21"/>
<wire x1="-0.55" y1="0.7" x2="-0.55" y2="2.9" width="0.35" layer="21"/>
<wire x1="0.55" y1="0.7" x2="0.55" y2="2.9" width="0.35" layer="21"/>
<wire x1="-1.6" y1="3" x2="1.6" y2="3" width="0.1" layer="21"/>
</package>
<package name="CRYSTAL-AB26T">
<pad name="1" x="-0.4" y="0" drill="0.4" diameter="0.6"/>
<pad name="2" x="0.4" y="0" drill="0.4" diameter="0.6"/>
<wire x1="-1.05" y1="3" x2="-1.05" y2="9.2" width="0.1" layer="21"/>
<wire x1="-1.05" y1="9.2" x2="1.05" y2="9.2" width="0.1" layer="21"/>
<wire x1="1.05" y1="9.2" x2="1.05" y2="3" width="0.1" layer="21"/>
<wire x1="-0.4" y1="0.7" x2="-0.4" y2="2.9" width="0.26" layer="21"/>
<wire x1="0.4" y1="0.7" x2="0.4" y2="2.9" width="0.26" layer="21"/>
<wire x1="-1.05" y1="3" x2="1.05" y2="3" width="0.1" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="CRYSTAL_3P">
<wire x1="1.016" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.016" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="1.524" x2="-0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-0.381" y1="-1.524" x2="0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="-1.524" x2="0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="1.524" x2="-0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="1.016" y1="1.778" x2="1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.778" x2="-1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.778" y1="1.905" x2="-1.778" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-1.778" y1="2.54" x2="1.778" y2="2.54" width="0.1524" layer="94"/>
<wire x1="1.778" y1="2.54" x2="1.778" y2="1.905" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-1.905" x2="1.778" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-1.778" y1="-2.54" x2="1.778" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-1.778" y1="-2.54" x2="-1.778" y2="-1.905" width="0.1524" layer="94"/>
<text x="2.54" y="1.016" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="3" x="2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
<pin name="2" x="0" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
<symbol name="SCHOTTKY-DIODE-A">
<wire x1="-1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="1.016" x2="0.635" y2="1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.905" y1="-1.016" x2="1.905" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="1.905" y2="-1.27" width="0.254" layer="94"/>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
</symbol>
<symbol name="DIODE-COMMON-V">
<text x="0" y="4.445" size="1.778" layer="95" align="bottom-center">&gt;PART</text>
<text x="0" y="-6.35" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<pin name="COMMON" x="0" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R90"/>
<wire x1="0" y1="-2.54" x2="0" y2="2.54" width="0.1524" layer="94"/>
<circle x="0" y="0" radius="0.127" width="0.4064" layer="94"/>
</symbol>
<symbol name="LED">
<wire x1="-1.27" y1="1.143" x2="0" y2="-0.889" width="0.254" layer="94"/>
<wire x1="0" y1="-0.889" x2="1.27" y2="1.143" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-0.889" x2="0" y2="-0.889" width="0.254" layer="94"/>
<wire x1="0" y1="-0.889" x2="1.27" y2="-0.889" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.143" x2="1.27" y2="1.143" width="0.254" layer="94"/>
<wire x1="2.032" y1="0.889" x2="2.921" y2="0" width="0.1524" layer="94"/>
<wire x1="1.27" y1="0.127" x2="2.159" y2="-0.762" width="0.1524" layer="94"/>
<pin name="K" x="0" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<polygon width="0.1524" layer="94">
<vertex x="3.048" y="0.381"/>
<vertex x="3.302" y="-0.381"/>
<vertex x="2.54" y="-0.127"/>
</polygon>
<polygon width="0.1524" layer="94">
<vertex x="2.286" y="-0.381"/>
<vertex x="2.54" y="-1.143"/>
<vertex x="1.778" y="-0.889"/>
</polygon>
<pin name="A" x="0" y="2.54" visible="off" length="short" direction="pas" rot="R270"/>
<text x="-4.445" y="0" size="1.778" layer="95" rot="R90" align="bottom-center">&gt;NAME</text>
<text x="-1.905" y="0" size="1.778" layer="96" rot="R90" align="bottom-center">&gt;VALUE</text>
</symbol>
<symbol name="CRYSTAL">
<wire x1="1.016" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.016" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="1.524" x2="-0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-0.381" y1="-1.524" x2="0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="-1.524" x2="0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="1.524" x2="-0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="1.016" y1="1.778" x2="1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.778" x2="-1.016" y2="-1.778" width="0.254" layer="94"/>
<text x="2.54" y="1.016" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="3" x="2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CSTCE">
<description>&lt;b&gt;muRata Ceramic Resonators&lt;/b&gt;&lt;br&gt;
CSTCE series &lt;br&gt;&lt;br&gt;</description>
<gates>
<gate name="G$1" symbol="CRYSTAL_3P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CSTCE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="8M00G15C"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BAS40-05" prefix="D">
<description>&lt;b&gt;Schottky Diode&lt;/b&gt; Common Cathode&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="SCHOTTKY-DIODE-A" x="-2.54" y="2.54" addlevel="always" swaplevel="1"/>
<gate name="G$2" symbol="SCHOTTKY-DIODE-A" x="-2.54" y="-2.54" addlevel="always" swaplevel="1"/>
<gate name="G$3" symbol="DIODE-COMMON-V" x="0" y="0" addlevel="must"/>
</gates>
<devices>
<device name="" package="SOT-23">
<connects>
<connect gate="G$1" pin="A" pad="1"/>
<connect gate="G$2" pin="A" pad="2"/>
<connect gate="G$3" pin="COMMON" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="W" package="SOT-323">
<connects>
<connect gate="G$1" pin="A" pad="1"/>
<connect gate="G$2" pin="A" pad="2"/>
<connect gate="G$3" pin="COMMON" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VLM*" prefix="D">
<description>&lt;b&gt;Vishay 0603 Highbright ChipLED&lt;/b&gt;&lt;p&gt;

VLMS1300 Super red &lt;p&gt;
VLMO1300 Soft orange &lt;p&gt;
VLMY1300 Yellow &lt;p&gt;
VLMG1300 Yellow green &lt;p&gt;
VLMTG1300 True green &lt;p&gt;
VLMB1300 Blue &lt;p&gt;
VLMB1310 Blue &lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="D0603-R">
<connects>
<connect gate="G$1" pin="A" pad="1"/>
<connect gate="G$1" pin="K" pad="2"/>
</connects>
<technologies>
<technology name="B1300-GS08"/>
<technology name="B1310-GS08"/>
<technology name="G1300-GS08"/>
<technology name="O1300-GS08"/>
<technology name="S1300-GS08"/>
<technology name="TG1300-GS08"/>
<technology name="Y1300-GS08"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="AB?T" prefix="Y">
<gates>
<gate name="G$1" symbol="CRYSTAL" x="0" y="0"/>
</gates>
<devices>
<device name="26" package="CRYSTAL-AB26T">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="3" pad="2"/>
</connects>
<technologies>
<technology name="-32.768KHZ"/>
</technologies>
</device>
<device name="38" package="CRYSTAL-AB38T">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="3" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply">
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="0" y="-2.54" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="+5V">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-1.905" y="-1.27" size="1.778" layer="96" rot="R90" align="bottom-center">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="+3V3">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-1.905" y="-1.27" size="1.778" layer="96" rot="R90" align="bottom-center">&gt;VALUE</text>
<pin name="+3V3" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
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
<deviceset name="+5V" prefix="+5V">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+3V3" prefix="+3V3">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+3V3" x="0" y="0"/>
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
<library name="misc">
<packages>
<package name="SWITCH-KMR-SERIES">
<smd name="1" x="-2.05" y="-0.8" dx="1" dy="0.9" layer="1" rot="R90"/>
<smd name="2" x="2.05" y="-0.8" dx="1" dy="0.9" layer="1" rot="R90"/>
<smd name="4" x="-2.05" y="0.8" dx="1" dy="0.9" layer="1" rot="R90"/>
<smd name="3" x="2.05" y="0.8" dx="1" dy="0.9" layer="1" rot="R90"/>
<wire x1="2.1" y1="1.4" x2="2.1" y2="-1.4" width="0.1" layer="51"/>
<wire x1="-2.1" y1="-1.4" x2="-2.1" y2="1.4" width="0.1" layer="51"/>
<wire x1="1" y1="0.25" x2="1" y2="-0.25" width="0.1" layer="21"/>
<wire x1="-1" y1="-0.25" x2="-1" y2="0.25" width="0.1" layer="21"/>
<wire x1="-1" y1="0.25" x2="-0.45" y2="0.8" width="0.1" layer="21" curve="-90"/>
<wire x1="-0.45" y1="0.8" x2="0.45" y2="0.8" width="0.1" layer="21"/>
<wire x1="0.45" y1="0.8" x2="1" y2="0.25" width="0.1" layer="21" curve="-90"/>
<wire x1="1" y1="-0.25" x2="0.45" y2="-0.8" width="0.1" layer="21" curve="-90"/>
<wire x1="0.45" y1="-0.8" x2="-0.45" y2="-0.8" width="0.1" layer="21"/>
<wire x1="-0.45" y1="-0.8" x2="-1" y2="-0.25" width="0.1" layer="21" curve="-90"/>
<wire x1="-1.25" y1="1.4" x2="1.25" y2="1.4" width="0.1" layer="21"/>
<wire x1="-1.25" y1="-1.4" x2="1.25" y2="-1.4" width="0.1" layer="21"/>
<wire x1="-2.1" y1="1.4" x2="-1.25" y2="1.4" width="0.1" layer="51"/>
<wire x1="1.25" y1="1.4" x2="2.1" y2="1.4" width="0.1" layer="51"/>
<wire x1="-2.1" y1="-1.4" x2="-1.25" y2="-1.4" width="0.1" layer="51"/>
<wire x1="1.25" y1="-1.4" x2="2.1" y2="-1.4" width="0.1" layer="51"/>
</package>
<package name="JP1">
<description>&lt;b&gt;JUMPER&lt;/b&gt;</description>
<wire x1="0" y1="1.016" x2="0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="1.016" x2="-0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.016" x2="0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.016" x2="-0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-1.27" x2="-2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.016" x2="-2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.27" x2="2.54" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.27" x2="0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.016" x2="2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.27" x2="2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.27" x2="0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="1.27" x2="-2.286" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.016" x2="-2.286" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.016" x2="-2.54" y2="-1.016" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="1" diameter="1.7" shape="square" rot="R270"/>
<pad name="2" x="1.27" y="0" drill="1" diameter="1.7" rot="R270"/>
<text x="0" y="1.5" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.5" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="0.9652" y1="-0.3048" x2="1.5748" y2="0.3048" layer="51" rot="R270"/>
<rectangle x1="-1.5748" y1="-0.3048" x2="-0.9652" y2="0.3048" layer="51" rot="R270"/>
</package>
<package name="JP-2.00">
<wire x1="0" y1="0.766" x2="0.254" y2="1.02" width="0.1524" layer="21"/>
<wire x1="0" y1="0.766" x2="-0.254" y2="1.02" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.766" x2="0.254" y2="-1.02" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.766" x2="-0.254" y2="-1.02" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-1.02" x2="-1.786" y2="-1.02" width="0.1524" layer="21"/>
<wire x1="-2.04" y1="-0.766" x2="-1.786" y2="-1.02" width="0.1524" layer="21"/>
<wire x1="1.786" y1="-1.02" x2="2.04" y2="-0.766" width="0.1524" layer="21"/>
<wire x1="1.786" y1="-1.02" x2="0.254" y2="-1.02" width="0.1524" layer="21"/>
<wire x1="2.04" y1="-0.766" x2="2.04" y2="0.766" width="0.1524" layer="21"/>
<wire x1="1.786" y1="1.02" x2="2.04" y2="0.766" width="0.1524" layer="21"/>
<wire x1="1.786" y1="1.02" x2="0.254" y2="1.02" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="1.02" x2="-1.786" y2="1.02" width="0.1524" layer="21"/>
<wire x1="-2.04" y1="0.766" x2="-1.786" y2="1.02" width="0.1524" layer="21"/>
<wire x1="-2.04" y1="0.766" x2="-2.04" y2="-0.766" width="0.1524" layer="21"/>
<pad name="1" x="-1.02" y="0" drill="0.8" diameter="1.5" shape="square" rot="R270"/>
<pad name="2" x="1.02" y="0" drill="0.8" diameter="1.5" rot="R270"/>
<text x="0" y="1.25" size="1" layer="25" ratio="10" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.5" size="1" layer="27" ratio="10" align="bottom-center">&gt;VALUE</text>
<rectangle x1="0.7152" y1="-0.3048" x2="1.3248" y2="0.3048" layer="51" rot="R270"/>
<rectangle x1="-1.3248" y1="-0.3048" x2="-0.7152" y2="0.3048" layer="51" rot="R270"/>
</package>
<package name="JP2-2.54-0.9-R">
<wire x1="0" y1="1.016" x2="0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="1.016" x2="-0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.016" x2="0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.016" x2="-0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-1.27" x2="-2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.016" x2="-2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.27" x2="2.54" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.27" x2="0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.016" x2="2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.27" x2="2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.27" x2="0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="1.27" x2="-2.286" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.016" x2="-2.286" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.016" x2="-2.54" y2="-1.016" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="0.9" rot="R270"/>
<pad name="2" x="1.27" y="0" drill="0.9" rot="R270"/>
<text x="0" y="1.5" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.5" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="0.9652" y1="-0.3048" x2="1.5748" y2="0.3048" layer="51" rot="R270"/>
<rectangle x1="-1.5748" y1="-0.3048" x2="-0.9652" y2="0.3048" layer="51" rot="R270"/>
</package>
<package name="0603-R">
<description>&lt;b&gt;Chip Capacitor 0603 reflow solder&lt;/b&gt;
&lt;p&gt;
Metric Code Size 1608</description>
<text x="0" y="0.75" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.75" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-0.725" y1="0.35" x2="0.725" y2="0.35" width="0.1016" layer="51"/>
<wire x1="0.725" y1="-0.35" x2="-0.725" y2="-0.35" width="0.1016" layer="51"/>
<smd name="1" x="-0.75" y="0" dx="1" dy="1" layer="1"/>
<smd name="2" x="0.75" y="0" dx="1" dy="1" layer="1"/>
<rectangle x1="-0.8" y1="-0.4" x2="-0.45" y2="0.4" layer="51"/>
<rectangle x1="0.45" y1="-0.4" x2="0.8" y2="0.4" layer="51"/>
</package>
<package name="JP-SMD-1.2X1.8">
<smd name="1" x="-0.7" y="0" dx="1.8" dy="1.2" layer="1" rot="R90"/>
<smd name="2" x="0.7" y="0" dx="1.8" dy="1.2" layer="1" rot="R90"/>
</package>
</packages>
<symbols>
<symbol name="FRAME_A3L">
<frame x1="0" y1="0" x2="387.35" y2="260.35" columns="8" rows="5" layer="94"/>
</symbol>
<symbol name="DOCFIELD-HSLU">
<wire x1="-104.14" y1="20.32" x2="-40.64" y2="20.32" width="0.1016" layer="94"/>
<text x="-38.1" y="14.605" size="3.556" layer="94" ratio="15">HSLU T&amp;A</text>
<text x="-38.1" y="1.905" size="1.778" layer="94">Technikumstrasse 21
CH-6048 Horw
https://www.hslu.ch
christian.jost@hslu.ch</text>
<wire x1="-40.64" y1="20.32" x2="0" y2="20.32" width="0.1016" layer="94"/>
<wire x1="-40.64" y1="20.32" x2="-40.64" y2="13.97" width="0.1016" layer="94"/>
<text x="-102.87" y="8.255" size="1.778" layer="94" align="center-left">Drawn by:</text>
<text x="-102.87" y="4.445" size="1.778" layer="94" align="center-left">Date:</text>
<text x="-102.87" y="1.27" size="1.016" layer="94" align="center-left">$Id: $</text>
<text x="-60.96" y="8.255" size="1.778" layer="94" align="center-left">Rev.:</text>
<wire x1="-40.64" y1="13.97" x2="-40.64" y2="10.16" width="0.1016" layer="94"/>
<wire x1="-40.64" y1="10.16" x2="-40.64" y2="6.35" width="0.1016" layer="94"/>
<wire x1="-40.64" y1="6.35" x2="-40.64" y2="2.54" width="0.1016" layer="94"/>
<wire x1="-40.64" y1="2.54" x2="-40.64" y2="0" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="10.16" x2="-62.23" y2="10.16" width="0.1016" layer="94"/>
<wire x1="-62.23" y1="10.16" x2="-40.64" y2="10.16" width="0.1016" layer="94"/>
<wire x1="-40.64" y1="6.35" x2="-62.23" y2="6.35" width="0.1016" layer="94"/>
<text x="-60.96" y="4.445" size="1.778" layer="94" align="center-left">Sheet:</text>
<wire x1="-62.23" y1="6.35" x2="-104.14" y2="6.35" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="0" x2="-40.64" y2="0" width="0.1016" layer="94"/>
<wire x1="-40.64" y1="0" x2="0" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="20.32" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="20.32" x2="-104.14" y2="13.97" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="13.97" x2="-104.14" y2="10.16" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="10.16" x2="-104.14" y2="6.35" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="6.35" x2="-104.14" y2="2.54" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="2.54" x2="-104.14" y2="0" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="2.54" x2="-62.23" y2="2.54" width="0.1016" layer="94"/>
<wire x1="-62.23" y1="2.54" x2="-40.64" y2="2.54" width="0.1016" layer="94"/>
<text x="-51.435" y="4.445" size="1.778" layer="94" ratio="12" align="center-left">&gt;SHEET</text>
<text x="-93.98" y="4.445" size="1.778" layer="94" ratio="12" align="center-left">&gt;LAST_DATE_TIME</text>
<text x="-88.265" y="8.255" size="1.778" layer="94" ratio="12" align="center-left">&gt;DRAWN_BY</text>
<text x="-51.435" y="8.255" size="1.778" layer="94" ratio="12" align="center-left">&gt;REV</text>
<text x="-102.87" y="12.065" size="1.778" layer="94" align="center-left">Project:</text>
<text x="-90.17" y="12.065" size="1.778" layer="94" ratio="12" align="center-left">&gt;PROJECT</text>
<wire x1="-104.14" y1="13.97" x2="-40.64" y2="13.97" width="0.1016" layer="94"/>
<wire x1="-62.23" y1="6.35" x2="-62.23" y2="2.54" width="0.1016" layer="94"/>
<text x="-102.87" y="17.145" size="2.54" layer="94" ratio="12" align="center-left">&gt;TITLE</text>
<wire x1="-62.23" y1="10.16" x2="-62.23" y2="6.35" width="0.1016" layer="94"/>
</symbol>
<symbol name="TASTER-1S">
<wire x1="1.905" y1="5.08" x2="0" y2="5.08" width="0.254" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="4.445" width="0.1524" layer="94"/>
<wire x1="0" y1="5.08" x2="-1.905" y2="5.08" width="0.254" layer="94"/>
<wire x1="0" y1="3.81" x2="0" y2="3.302" width="0.1524" layer="94"/>
<wire x1="0" y1="2.286" x2="0" y2="1.905" width="0.1524" layer="94"/>
<wire x1="-3.175" y1="0" x2="-1.905" y2="0" width="0.254" layer="94"/>
<wire x1="-1.905" y1="0" x2="3.175" y2="1.905" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="3.81" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="94"/>
<wire x1="0" y1="3.302" x2="-0.762" y2="2.794" width="0.1524" layer="94"/>
<wire x1="-0.762" y1="2.794" x2="0" y2="2.286" width="0.1524" layer="94"/>
<text x="-1.905" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="C" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
<pin name="S" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="JP1">
<wire x1="0" y1="0" x2="0" y2="1.27" width="0.1524" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="1.27" width="0.4064" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="1.27" width="0.1524" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="1.27" width="0.4064" layer="94"/>
<wire x1="-0.635" y1="0" x2="3.175" y2="0" width="0.4064" layer="94"/>
<wire x1="3.175" y1="0" x2="3.175" y2="0.635" width="0.4064" layer="94"/>
<wire x1="3.175" y1="0.635" x2="-0.635" y2="0.635" width="0.4064" layer="94"/>
<wire x1="-0.635" y1="0.635" x2="-0.635" y2="0" width="0.4064" layer="94"/>
<text x="-1.27" y="0" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<pin name="1" x="0" y="-2.54" visible="pad" length="short" direction="pas" swaplevel="1" rot="R90"/>
<pin name="2" x="2.54" y="-2.54" visible="pad" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="JP">
<wire x1="-0.635" y1="0" x2="-0.635" y2="2.54" width="0.127" layer="94"/>
<wire x1="-0.635" y1="2.54" x2="-0.3175" y2="2.54" width="0.127" layer="94"/>
<wire x1="-0.3175" y1="2.54" x2="-0.3175" y2="2.8575" width="0.127" layer="94"/>
<wire x1="-0.3175" y1="2.8575" x2="-0.635" y2="2.8575" width="0.127" layer="94"/>
<wire x1="-0.635" y1="2.8575" x2="-0.635" y2="3.4925" width="0.127" layer="94"/>
<wire x1="-0.635" y1="3.4925" x2="0.635" y2="3.4925" width="0.127" layer="94"/>
<wire x1="0.635" y1="3.4925" x2="0.635" y2="3.175" width="0.127" layer="94"/>
<wire x1="0.635" y1="3.175" x2="0.635" y2="2.8575" width="0.127" layer="94"/>
<wire x1="0.635" y1="2.8575" x2="0.635" y2="2.54" width="0.127" layer="94"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.127" layer="94"/>
<wire x1="1.905" y1="2.54" x2="1.905" y2="2.8575" width="0.127" layer="94"/>
<wire x1="1.905" y1="2.8575" x2="1.905" y2="3.175" width="0.127" layer="94"/>
<wire x1="1.905" y1="3.175" x2="1.905" y2="3.4925" width="0.127" layer="94"/>
<wire x1="1.905" y1="3.4925" x2="3.175" y2="3.4925" width="0.127" layer="94"/>
<wire x1="3.175" y1="3.4925" x2="3.175" y2="2.8575" width="0.127" layer="94"/>
<wire x1="3.175" y1="2.8575" x2="2.8575" y2="2.8575" width="0.127" layer="94"/>
<wire x1="2.8575" y1="2.8575" x2="2.8575" y2="2.54" width="0.127" layer="94"/>
<wire x1="2.8575" y1="2.54" x2="3.175" y2="2.54" width="0.127" layer="94"/>
<wire x1="3.175" y1="2.54" x2="3.175" y2="0" width="0.127" layer="94"/>
<wire x1="0.635" y1="3.175" x2="1.905" y2="3.175" width="0.127" layer="94"/>
<wire x1="0.635" y1="2.8575" x2="1.905" y2="2.8575" width="0.127" layer="94"/>
<wire x1="-0.635" y1="0" x2="3.175" y2="0" width="0.127" layer="94"/>
</symbol>
<symbol name="FUSE">
<wire x1="-2.54" y1="-0.762" x2="2.54" y2="-0.762" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.762" x2="-2.54" y2="0.762" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.762" x2="2.54" y2="0.762" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0.762" x2="-2.54" y2="-0.762" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="1.397" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-2.921" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="3.81" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-3.81" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRAME_A3L-DOC-HSLU">
<description>&lt;b&gt;FRAME HSLU&lt;/b&gt;
&lt;p&gt;
DIN A3, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="FRAME_A3L" x="0" y="0"/>
<gate name="G$2" symbol="DOCFIELD-HSLU" x="383.54" y="3.81"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="KMR2*" prefix="S">
<description>&lt;b&gt;SWITCH-KMR-SERIES&lt;/b&gt;
&lt;br&gt;
KMR2xyz?LFS
&lt;br&gt;&lt;br&gt;
Operating Force x
&lt;br&gt;
x=1 =&gt; 1.2 N &lt;br&gt;
x=2 =&gt; 2.0 N &lt;br&gt;
x=3 =&gt; 3.0 N &lt;br&gt;
x=5 =&gt; 4.0 N &lt;br&gt;
&lt;br&gt;
Contact material y
&lt;br&gt;
y=1 =&gt; Silver &lt;br&gt;
y=2 =&gt; Silver long life &lt;br&gt;
y=3 =&gt; Gold &lt;br&gt;
&lt;br&gt;
Grounding option z
&lt;br&gt;
z=G =&gt; Ground pin &lt;br&gt;
z=NG =&gt; No Ground pin &lt;br&gt;</description>
<gates>
<gate name="G$1" symbol="TASTER-1S" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SWITCH-KMR-SERIES">
<connects>
<connect gate="G$1" pin="C" pad="1 2"/>
<connect gate="G$1" pin="S" pad="3 4"/>
</connects>
<technologies>
<technology name="11G-LFS"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="JP1" prefix="JP">
<description>&lt;b&gt;JUMPER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="JP1" x="2.54" y="0"/>
<gate name="G$1" symbol="JP" x="2.54" y="0" addlevel="request"/>
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
<device name="JP-2.00" package="JP-2.00">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-2.54-0.9-R" package="JP2-2.54-0.9-R">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-SMD-1.2X1.8" package="JP-SMD-1.2X1.8">
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
<deviceset name="0603SFV*F/32-2" prefix="F">
<description>&lt;b&gt;0603 Very Fast-Acting Chip Fuses&lt;/b&gt;
&lt;p&gt;
TE connectivity</description>
<gates>
<gate name="G$1" symbol="FUSE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="0603-R">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="050"/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ICs">
<packages>
<package name="QFN48">
<description>&lt;b&gt;48-pin QFN 7 x 7 mm LF48&lt;/b&gt;&lt;p&gt;
48 Quad Flat Package No Leads&lt;br&gt;
Source: http://v4.cypress.com/cfuploads/img/products/cywusb6934.pdf</description>
<wire x1="-3" y1="3.5" x2="3" y2="3.5" width="0.1016" layer="51"/>
<wire x1="3" y1="3.5" x2="3.5" y2="3" width="0.1016" layer="51"/>
<wire x1="3.5" y1="3" x2="3.5" y2="-3" width="0.1016" layer="51"/>
<wire x1="3.5" y1="-3" x2="3" y2="-3.5" width="0.1016" layer="51"/>
<wire x1="3" y1="-3.5" x2="-3" y2="-3.5" width="0.1016" layer="51"/>
<wire x1="-3" y1="-3.5" x2="-3.5" y2="-3" width="0.1016" layer="51"/>
<wire x1="-3.5" y1="-3" x2="-3.5" y2="3" width="0.1016" layer="51"/>
<wire x1="-3.5" y1="3" x2="-3" y2="3.5" width="0.1016" layer="51"/>
<wire x1="-3.49" y1="2.84" x2="-3.06" y2="2.84" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="2.84" x2="-3.06" y2="2.66" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="2.66" x2="-3.49" y2="2.66" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="2.66" x2="-3.49" y2="2.84" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="2.75" x2="-3.11" y2="2.75" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="2.845" x2="-3.055" y2="2.845" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="2.845" x2="-3.055" y2="2.655" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="2.655" x2="-3.495" y2="2.655" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="2.655" x2="-3.495" y2="2.845" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="2.75" x2="-3.105" y2="2.75" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="2.34" x2="-3.06" y2="2.34" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="2.34" x2="-3.06" y2="2.16" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="2.16" x2="-3.49" y2="2.16" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="2.16" x2="-3.49" y2="2.34" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="2.25" x2="-3.11" y2="2.25" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="2.345" x2="-3.055" y2="2.345" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="2.345" x2="-3.055" y2="2.155" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="2.155" x2="-3.495" y2="2.155" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="2.155" x2="-3.495" y2="2.345" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="2.25" x2="-3.105" y2="2.25" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="1.84" x2="-3.06" y2="1.84" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="1.84" x2="-3.06" y2="1.66" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="1.66" x2="-3.49" y2="1.66" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="1.66" x2="-3.49" y2="1.84" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="1.75" x2="-3.11" y2="1.75" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="1.845" x2="-3.055" y2="1.845" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="1.845" x2="-3.055" y2="1.655" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="1.655" x2="-3.495" y2="1.655" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="1.655" x2="-3.495" y2="1.845" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="1.75" x2="-3.105" y2="1.75" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="1.34" x2="-3.06" y2="1.34" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="1.34" x2="-3.06" y2="1.16" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="1.16" x2="-3.49" y2="1.16" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="1.16" x2="-3.49" y2="1.34" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="1.25" x2="-3.11" y2="1.25" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="1.345" x2="-3.055" y2="1.345" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="1.345" x2="-3.055" y2="1.155" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="1.155" x2="-3.495" y2="1.155" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="1.155" x2="-3.495" y2="1.345" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="1.25" x2="-3.105" y2="1.25" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="0.84" x2="-3.06" y2="0.84" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="0.84" x2="-3.06" y2="0.66" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="0.66" x2="-3.49" y2="0.66" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="0.66" x2="-3.49" y2="0.84" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="0.75" x2="-3.11" y2="0.75" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="0.845" x2="-3.055" y2="0.845" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="0.845" x2="-3.055" y2="0.655" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="0.655" x2="-3.495" y2="0.655" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="0.655" x2="-3.495" y2="0.845" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="0.75" x2="-3.105" y2="0.75" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="0.34" x2="-3.06" y2="0.34" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="0.34" x2="-3.06" y2="0.16" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="0.16" x2="-3.49" y2="0.16" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="0.16" x2="-3.49" y2="0.34" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="0.25" x2="-3.11" y2="0.25" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="0.345" x2="-3.055" y2="0.345" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="0.345" x2="-3.055" y2="0.155" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="0.155" x2="-3.495" y2="0.155" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="0.155" x2="-3.495" y2="0.345" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="0.25" x2="-3.105" y2="0.25" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="-0.16" x2="-3.06" y2="-0.16" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-0.16" x2="-3.06" y2="-0.34" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-0.34" x2="-3.49" y2="-0.34" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="-0.34" x2="-3.49" y2="-0.16" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="-0.25" x2="-3.11" y2="-0.25" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="-0.155" x2="-3.055" y2="-0.155" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-0.155" x2="-3.055" y2="-0.345" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-0.345" x2="-3.495" y2="-0.345" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="-0.345" x2="-3.495" y2="-0.155" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="-0.25" x2="-3.105" y2="-0.25" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="-0.66" x2="-3.06" y2="-0.66" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-0.66" x2="-3.06" y2="-0.84" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-0.84" x2="-3.49" y2="-0.84" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="-0.84" x2="-3.49" y2="-0.66" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="-0.75" x2="-3.11" y2="-0.75" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="-0.655" x2="-3.055" y2="-0.655" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-0.655" x2="-3.055" y2="-0.845" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-0.845" x2="-3.495" y2="-0.845" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="-0.845" x2="-3.495" y2="-0.655" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="-0.75" x2="-3.105" y2="-0.75" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="-1.16" x2="-3.06" y2="-1.16" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-1.16" x2="-3.06" y2="-1.34" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-1.34" x2="-3.49" y2="-1.34" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="-1.34" x2="-3.49" y2="-1.16" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="-1.25" x2="-3.11" y2="-1.25" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="-1.155" x2="-3.055" y2="-1.155" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-1.155" x2="-3.055" y2="-1.345" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-1.345" x2="-3.495" y2="-1.345" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="-1.345" x2="-3.495" y2="-1.155" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="-1.25" x2="-3.105" y2="-1.25" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="-1.66" x2="-3.06" y2="-1.66" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-1.66" x2="-3.06" y2="-1.84" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-1.84" x2="-3.49" y2="-1.84" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="-1.84" x2="-3.49" y2="-1.66" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="-1.75" x2="-3.11" y2="-1.75" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="-1.655" x2="-3.055" y2="-1.655" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-1.655" x2="-3.055" y2="-1.845" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-1.845" x2="-3.495" y2="-1.845" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="-1.845" x2="-3.495" y2="-1.655" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="-1.75" x2="-3.105" y2="-1.75" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="-2.16" x2="-3.06" y2="-2.16" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-2.16" x2="-3.06" y2="-2.34" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-2.34" x2="-3.49" y2="-2.34" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="-2.34" x2="-3.49" y2="-2.16" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="-2.25" x2="-3.11" y2="-2.25" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="-2.155" x2="-3.055" y2="-2.155" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-2.155" x2="-3.055" y2="-2.345" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-2.345" x2="-3.495" y2="-2.345" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="-2.345" x2="-3.495" y2="-2.155" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="-2.25" x2="-3.105" y2="-2.25" width="0.1016" layer="29"/>
<wire x1="-3.49" y1="-2.66" x2="-3.06" y2="-2.66" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-2.66" x2="-3.06" y2="-2.84" width="0.1016" layer="31"/>
<wire x1="-3.06" y1="-2.84" x2="-3.49" y2="-2.84" width="0.1016" layer="31"/>
<wire x1="-3.49" y1="-2.84" x2="-3.49" y2="-2.66" width="0.1016" layer="31"/>
<wire x1="-3.44" y1="-2.75" x2="-3.11" y2="-2.75" width="0.1016" layer="31"/>
<wire x1="-3.495" y1="-2.655" x2="-3.055" y2="-2.655" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-2.655" x2="-3.055" y2="-2.845" width="0.1016" layer="29"/>
<wire x1="-3.055" y1="-2.845" x2="-3.495" y2="-2.845" width="0.1016" layer="29"/>
<wire x1="-3.495" y1="-2.845" x2="-3.495" y2="-2.655" width="0.1016" layer="29"/>
<wire x1="-3.445" y1="-2.75" x2="-3.105" y2="-2.75" width="0.1016" layer="29"/>
<wire x1="-2.84" y1="-3.49" x2="-2.84" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-2.84" y1="-3.06" x2="-2.66" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-2.66" y1="-3.06" x2="-2.66" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-2.66" y1="-3.49" x2="-2.84" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-2.75" y1="-3.44" x2="-2.75" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="-2.845" y1="-3.495" x2="-2.845" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-2.845" y1="-3.055" x2="-2.655" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-2.655" y1="-3.055" x2="-2.655" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-2.655" y1="-3.495" x2="-2.845" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-2.75" y1="-3.445" x2="-2.75" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="-2.34" y1="-3.49" x2="-2.34" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-2.34" y1="-3.06" x2="-2.16" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-2.16" y1="-3.06" x2="-2.16" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-2.16" y1="-3.49" x2="-2.34" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-2.25" y1="-3.44" x2="-2.25" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="-2.345" y1="-3.495" x2="-2.345" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-2.345" y1="-3.055" x2="-2.155" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-2.155" y1="-3.055" x2="-2.155" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-2.155" y1="-3.495" x2="-2.345" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-2.25" y1="-3.445" x2="-2.25" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="-1.84" y1="-3.49" x2="-1.84" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-1.84" y1="-3.06" x2="-1.66" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-1.66" y1="-3.06" x2="-1.66" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-1.66" y1="-3.49" x2="-1.84" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-1.75" y1="-3.44" x2="-1.75" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="-1.845" y1="-3.495" x2="-1.845" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-1.845" y1="-3.055" x2="-1.655" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-1.655" y1="-3.055" x2="-1.655" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-1.655" y1="-3.495" x2="-1.845" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-1.75" y1="-3.445" x2="-1.75" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="-1.34" y1="-3.49" x2="-1.34" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-1.34" y1="-3.06" x2="-1.16" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-1.16" y1="-3.06" x2="-1.16" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-1.16" y1="-3.49" x2="-1.34" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-1.25" y1="-3.44" x2="-1.25" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="-1.345" y1="-3.495" x2="-1.345" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-1.345" y1="-3.055" x2="-1.155" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-1.155" y1="-3.055" x2="-1.155" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-1.155" y1="-3.495" x2="-1.345" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-1.25" y1="-3.445" x2="-1.25" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="-0.84" y1="-3.49" x2="-0.84" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-0.84" y1="-3.06" x2="-0.66" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-0.66" y1="-3.06" x2="-0.66" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-0.66" y1="-3.49" x2="-0.84" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-0.75" y1="-3.44" x2="-0.75" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="-0.845" y1="-3.495" x2="-0.845" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-0.845" y1="-3.055" x2="-0.655" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-0.655" y1="-3.055" x2="-0.655" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-0.655" y1="-3.495" x2="-0.845" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-0.75" y1="-3.445" x2="-0.75" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="-0.34" y1="-3.49" x2="-0.34" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-0.34" y1="-3.06" x2="-0.16" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="-0.16" y1="-3.06" x2="-0.16" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-0.16" y1="-3.49" x2="-0.34" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="-0.25" y1="-3.44" x2="-0.25" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="-0.345" y1="-3.495" x2="-0.345" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-0.345" y1="-3.055" x2="-0.155" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="-0.155" y1="-3.055" x2="-0.155" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-0.155" y1="-3.495" x2="-0.345" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="-0.25" y1="-3.445" x2="-0.25" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="0.16" y1="-3.49" x2="0.16" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="0.16" y1="-3.06" x2="0.34" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="0.34" y1="-3.06" x2="0.34" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="0.34" y1="-3.49" x2="0.16" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="0.25" y1="-3.44" x2="0.25" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="0.155" y1="-3.495" x2="0.155" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="0.155" y1="-3.055" x2="0.345" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="0.345" y1="-3.055" x2="0.345" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="0.345" y1="-3.495" x2="0.155" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="0.25" y1="-3.445" x2="0.25" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="0.66" y1="-3.49" x2="0.66" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="0.66" y1="-3.06" x2="0.84" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="0.84" y1="-3.06" x2="0.84" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="0.84" y1="-3.49" x2="0.66" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="0.75" y1="-3.44" x2="0.75" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="0.655" y1="-3.495" x2="0.655" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="0.655" y1="-3.055" x2="0.845" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="0.845" y1="-3.055" x2="0.845" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="0.845" y1="-3.495" x2="0.655" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="0.75" y1="-3.445" x2="0.75" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="1.16" y1="-3.49" x2="1.16" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="1.16" y1="-3.06" x2="1.34" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="1.34" y1="-3.06" x2="1.34" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="1.34" y1="-3.49" x2="1.16" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="1.25" y1="-3.44" x2="1.25" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="1.155" y1="-3.495" x2="1.155" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="1.155" y1="-3.055" x2="1.345" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="1.345" y1="-3.055" x2="1.345" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="1.345" y1="-3.495" x2="1.155" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="1.25" y1="-3.445" x2="1.25" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="1.66" y1="-3.49" x2="1.66" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="1.66" y1="-3.06" x2="1.84" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="1.84" y1="-3.06" x2="1.84" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="1.84" y1="-3.49" x2="1.66" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="1.75" y1="-3.44" x2="1.75" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="1.655" y1="-3.495" x2="1.655" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="1.655" y1="-3.055" x2="1.845" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="1.845" y1="-3.055" x2="1.845" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="1.845" y1="-3.495" x2="1.655" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="1.75" y1="-3.445" x2="1.75" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="2.16" y1="-3.49" x2="2.16" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="2.16" y1="-3.06" x2="2.34" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="2.34" y1="-3.06" x2="2.34" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="2.34" y1="-3.49" x2="2.16" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="2.25" y1="-3.44" x2="2.25" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="2.155" y1="-3.495" x2="2.155" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="2.155" y1="-3.055" x2="2.345" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="2.345" y1="-3.055" x2="2.345" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="2.345" y1="-3.495" x2="2.155" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="2.25" y1="-3.445" x2="2.25" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="2.66" y1="-3.49" x2="2.66" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="2.66" y1="-3.06" x2="2.84" y2="-3.06" width="0.1016" layer="31"/>
<wire x1="2.84" y1="-3.06" x2="2.84" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="2.84" y1="-3.49" x2="2.66" y2="-3.49" width="0.1016" layer="31"/>
<wire x1="2.75" y1="-3.44" x2="2.75" y2="-3.11" width="0.1016" layer="31"/>
<wire x1="2.655" y1="-3.495" x2="2.655" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="2.655" y1="-3.055" x2="2.845" y2="-3.055" width="0.1016" layer="29"/>
<wire x1="2.845" y1="-3.055" x2="2.845" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="2.845" y1="-3.495" x2="2.655" y2="-3.495" width="0.1016" layer="29"/>
<wire x1="2.75" y1="-3.445" x2="2.75" y2="-3.105" width="0.1016" layer="29"/>
<wire x1="3.49" y1="-2.84" x2="3.06" y2="-2.84" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-2.84" x2="3.06" y2="-2.66" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-2.66" x2="3.49" y2="-2.66" width="0.1016" layer="31"/>
<wire x1="3.49" y1="-2.66" x2="3.49" y2="-2.84" width="0.1016" layer="31"/>
<wire x1="3.44" y1="-2.75" x2="3.11" y2="-2.75" width="0.1016" layer="31"/>
<wire x1="3.495" y1="-2.845" x2="3.055" y2="-2.845" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-2.845" x2="3.055" y2="-2.655" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-2.655" x2="3.495" y2="-2.655" width="0.1016" layer="29"/>
<wire x1="3.495" y1="-2.655" x2="3.495" y2="-2.845" width="0.1016" layer="29"/>
<wire x1="3.445" y1="-2.75" x2="3.105" y2="-2.75" width="0.1016" layer="29"/>
<wire x1="3.49" y1="-2.34" x2="3.06" y2="-2.34" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-2.34" x2="3.06" y2="-2.16" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-2.16" x2="3.49" y2="-2.16" width="0.1016" layer="31"/>
<wire x1="3.49" y1="-2.16" x2="3.49" y2="-2.34" width="0.1016" layer="31"/>
<wire x1="3.44" y1="-2.25" x2="3.11" y2="-2.25" width="0.1016" layer="31"/>
<wire x1="3.495" y1="-2.345" x2="3.055" y2="-2.345" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-2.345" x2="3.055" y2="-2.155" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-2.155" x2="3.495" y2="-2.155" width="0.1016" layer="29"/>
<wire x1="3.495" y1="-2.155" x2="3.495" y2="-2.345" width="0.1016" layer="29"/>
<wire x1="3.445" y1="-2.25" x2="3.105" y2="-2.25" width="0.1016" layer="29"/>
<wire x1="3.49" y1="-1.84" x2="3.06" y2="-1.84" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-1.84" x2="3.06" y2="-1.66" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-1.66" x2="3.49" y2="-1.66" width="0.1016" layer="31"/>
<wire x1="3.49" y1="-1.66" x2="3.49" y2="-1.84" width="0.1016" layer="31"/>
<wire x1="3.44" y1="-1.75" x2="3.11" y2="-1.75" width="0.1016" layer="31"/>
<wire x1="3.495" y1="-1.845" x2="3.055" y2="-1.845" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-1.845" x2="3.055" y2="-1.655" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-1.655" x2="3.495" y2="-1.655" width="0.1016" layer="29"/>
<wire x1="3.495" y1="-1.655" x2="3.495" y2="-1.845" width="0.1016" layer="29"/>
<wire x1="3.445" y1="-1.75" x2="3.105" y2="-1.75" width="0.1016" layer="29"/>
<wire x1="3.49" y1="-1.34" x2="3.06" y2="-1.34" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-1.34" x2="3.06" y2="-1.16" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-1.16" x2="3.49" y2="-1.16" width="0.1016" layer="31"/>
<wire x1="3.49" y1="-1.16" x2="3.49" y2="-1.34" width="0.1016" layer="31"/>
<wire x1="3.44" y1="-1.25" x2="3.11" y2="-1.25" width="0.1016" layer="31"/>
<wire x1="3.495" y1="-1.345" x2="3.055" y2="-1.345" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-1.345" x2="3.055" y2="-1.155" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-1.155" x2="3.495" y2="-1.155" width="0.1016" layer="29"/>
<wire x1="3.495" y1="-1.155" x2="3.495" y2="-1.345" width="0.1016" layer="29"/>
<wire x1="3.445" y1="-1.25" x2="3.105" y2="-1.25" width="0.1016" layer="29"/>
<wire x1="3.49" y1="-0.84" x2="3.06" y2="-0.84" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-0.84" x2="3.06" y2="-0.66" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-0.66" x2="3.49" y2="-0.66" width="0.1016" layer="31"/>
<wire x1="3.49" y1="-0.66" x2="3.49" y2="-0.84" width="0.1016" layer="31"/>
<wire x1="3.44" y1="-0.75" x2="3.11" y2="-0.75" width="0.1016" layer="31"/>
<wire x1="3.495" y1="-0.845" x2="3.055" y2="-0.845" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-0.845" x2="3.055" y2="-0.655" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-0.655" x2="3.495" y2="-0.655" width="0.1016" layer="29"/>
<wire x1="3.495" y1="-0.655" x2="3.495" y2="-0.845" width="0.1016" layer="29"/>
<wire x1="3.445" y1="-0.75" x2="3.105" y2="-0.75" width="0.1016" layer="29"/>
<wire x1="3.49" y1="-0.34" x2="3.06" y2="-0.34" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-0.34" x2="3.06" y2="-0.16" width="0.1016" layer="31"/>
<wire x1="3.06" y1="-0.16" x2="3.49" y2="-0.16" width="0.1016" layer="31"/>
<wire x1="3.49" y1="-0.16" x2="3.49" y2="-0.34" width="0.1016" layer="31"/>
<wire x1="3.44" y1="-0.25" x2="3.11" y2="-0.25" width="0.1016" layer="31"/>
<wire x1="3.495" y1="-0.345" x2="3.055" y2="-0.345" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-0.345" x2="3.055" y2="-0.155" width="0.1016" layer="29"/>
<wire x1="3.055" y1="-0.155" x2="3.495" y2="-0.155" width="0.1016" layer="29"/>
<wire x1="3.495" y1="-0.155" x2="3.495" y2="-0.345" width="0.1016" layer="29"/>
<wire x1="3.445" y1="-0.25" x2="3.105" y2="-0.25" width="0.1016" layer="29"/>
<wire x1="3.49" y1="0.16" x2="3.06" y2="0.16" width="0.1016" layer="31"/>
<wire x1="3.06" y1="0.16" x2="3.06" y2="0.34" width="0.1016" layer="31"/>
<wire x1="3.06" y1="0.34" x2="3.49" y2="0.34" width="0.1016" layer="31"/>
<wire x1="3.49" y1="0.34" x2="3.49" y2="0.16" width="0.1016" layer="31"/>
<wire x1="3.44" y1="0.25" x2="3.11" y2="0.25" width="0.1016" layer="31"/>
<wire x1="3.495" y1="0.155" x2="3.055" y2="0.155" width="0.1016" layer="29"/>
<wire x1="3.055" y1="0.155" x2="3.055" y2="0.345" width="0.1016" layer="29"/>
<wire x1="3.055" y1="0.345" x2="3.495" y2="0.345" width="0.1016" layer="29"/>
<wire x1="3.495" y1="0.345" x2="3.495" y2="0.155" width="0.1016" layer="29"/>
<wire x1="3.445" y1="0.25" x2="3.105" y2="0.25" width="0.1016" layer="29"/>
<wire x1="3.49" y1="0.66" x2="3.06" y2="0.66" width="0.1016" layer="31"/>
<wire x1="3.06" y1="0.66" x2="3.06" y2="0.84" width="0.1016" layer="31"/>
<wire x1="3.06" y1="0.84" x2="3.49" y2="0.84" width="0.1016" layer="31"/>
<wire x1="3.49" y1="0.84" x2="3.49" y2="0.66" width="0.1016" layer="31"/>
<wire x1="3.44" y1="0.75" x2="3.11" y2="0.75" width="0.1016" layer="31"/>
<wire x1="3.495" y1="0.655" x2="3.055" y2="0.655" width="0.1016" layer="29"/>
<wire x1="3.055" y1="0.655" x2="3.055" y2="0.845" width="0.1016" layer="29"/>
<wire x1="3.055" y1="0.845" x2="3.495" y2="0.845" width="0.1016" layer="29"/>
<wire x1="3.495" y1="0.845" x2="3.495" y2="0.655" width="0.1016" layer="29"/>
<wire x1="3.445" y1="0.75" x2="3.105" y2="0.75" width="0.1016" layer="29"/>
<wire x1="3.49" y1="1.16" x2="3.06" y2="1.16" width="0.1016" layer="31"/>
<wire x1="3.06" y1="1.16" x2="3.06" y2="1.34" width="0.1016" layer="31"/>
<wire x1="3.06" y1="1.34" x2="3.49" y2="1.34" width="0.1016" layer="31"/>
<wire x1="3.49" y1="1.34" x2="3.49" y2="1.16" width="0.1016" layer="31"/>
<wire x1="3.44" y1="1.25" x2="3.11" y2="1.25" width="0.1016" layer="31"/>
<wire x1="3.495" y1="1.155" x2="3.055" y2="1.155" width="0.1016" layer="29"/>
<wire x1="3.055" y1="1.155" x2="3.055" y2="1.345" width="0.1016" layer="29"/>
<wire x1="3.055" y1="1.345" x2="3.495" y2="1.345" width="0.1016" layer="29"/>
<wire x1="3.495" y1="1.345" x2="3.495" y2="1.155" width="0.1016" layer="29"/>
<wire x1="3.445" y1="1.25" x2="3.105" y2="1.25" width="0.1016" layer="29"/>
<wire x1="3.49" y1="1.66" x2="3.06" y2="1.66" width="0.1016" layer="31"/>
<wire x1="3.06" y1="1.66" x2="3.06" y2="1.84" width="0.1016" layer="31"/>
<wire x1="3.06" y1="1.84" x2="3.49" y2="1.84" width="0.1016" layer="31"/>
<wire x1="3.49" y1="1.84" x2="3.49" y2="1.66" width="0.1016" layer="31"/>
<wire x1="3.44" y1="1.75" x2="3.11" y2="1.75" width="0.1016" layer="31"/>
<wire x1="3.495" y1="1.655" x2="3.055" y2="1.655" width="0.1016" layer="29"/>
<wire x1="3.055" y1="1.655" x2="3.055" y2="1.845" width="0.1016" layer="29"/>
<wire x1="3.055" y1="1.845" x2="3.495" y2="1.845" width="0.1016" layer="29"/>
<wire x1="3.495" y1="1.845" x2="3.495" y2="1.655" width="0.1016" layer="29"/>
<wire x1="3.445" y1="1.75" x2="3.105" y2="1.75" width="0.1016" layer="29"/>
<wire x1="3.49" y1="2.16" x2="3.06" y2="2.16" width="0.1016" layer="31"/>
<wire x1="3.06" y1="2.16" x2="3.06" y2="2.34" width="0.1016" layer="31"/>
<wire x1="3.06" y1="2.34" x2="3.49" y2="2.34" width="0.1016" layer="31"/>
<wire x1="3.49" y1="2.34" x2="3.49" y2="2.16" width="0.1016" layer="31"/>
<wire x1="3.44" y1="2.25" x2="3.11" y2="2.25" width="0.1016" layer="31"/>
<wire x1="3.495" y1="2.155" x2="3.055" y2="2.155" width="0.1016" layer="29"/>
<wire x1="3.055" y1="2.155" x2="3.055" y2="2.345" width="0.1016" layer="29"/>
<wire x1="3.055" y1="2.345" x2="3.495" y2="2.345" width="0.1016" layer="29"/>
<wire x1="3.495" y1="2.345" x2="3.495" y2="2.155" width="0.1016" layer="29"/>
<wire x1="3.445" y1="2.25" x2="3.105" y2="2.25" width="0.1016" layer="29"/>
<wire x1="3.49" y1="2.66" x2="3.06" y2="2.66" width="0.1016" layer="31"/>
<wire x1="3.06" y1="2.66" x2="3.06" y2="2.84" width="0.1016" layer="31"/>
<wire x1="3.06" y1="2.84" x2="3.49" y2="2.84" width="0.1016" layer="31"/>
<wire x1="3.49" y1="2.84" x2="3.49" y2="2.66" width="0.1016" layer="31"/>
<wire x1="3.44" y1="2.75" x2="3.11" y2="2.75" width="0.1016" layer="31"/>
<wire x1="3.495" y1="2.655" x2="3.055" y2="2.655" width="0.1016" layer="29"/>
<wire x1="3.055" y1="2.655" x2="3.055" y2="2.845" width="0.1016" layer="29"/>
<wire x1="3.055" y1="2.845" x2="3.495" y2="2.845" width="0.1016" layer="29"/>
<wire x1="3.495" y1="2.845" x2="3.495" y2="2.655" width="0.1016" layer="29"/>
<wire x1="3.445" y1="2.75" x2="3.105" y2="2.75" width="0.1016" layer="29"/>
<wire x1="2.84" y1="3.49" x2="2.84" y2="3.06" width="0.1016" layer="31"/>
<wire x1="2.84" y1="3.06" x2="2.66" y2="3.06" width="0.1016" layer="31"/>
<wire x1="2.66" y1="3.06" x2="2.66" y2="3.49" width="0.1016" layer="31"/>
<wire x1="2.66" y1="3.49" x2="2.84" y2="3.49" width="0.1016" layer="31"/>
<wire x1="2.75" y1="3.44" x2="2.75" y2="3.11" width="0.1016" layer="31"/>
<wire x1="2.845" y1="3.495" x2="2.845" y2="3.055" width="0.1016" layer="29"/>
<wire x1="2.845" y1="3.055" x2="2.655" y2="3.055" width="0.1016" layer="29"/>
<wire x1="2.655" y1="3.055" x2="2.655" y2="3.495" width="0.1016" layer="29"/>
<wire x1="2.655" y1="3.495" x2="2.845" y2="3.495" width="0.1016" layer="29"/>
<wire x1="2.75" y1="3.445" x2="2.75" y2="3.105" width="0.1016" layer="29"/>
<wire x1="2.34" y1="3.49" x2="2.34" y2="3.06" width="0.1016" layer="31"/>
<wire x1="2.34" y1="3.06" x2="2.16" y2="3.06" width="0.1016" layer="31"/>
<wire x1="2.16" y1="3.06" x2="2.16" y2="3.49" width="0.1016" layer="31"/>
<wire x1="2.16" y1="3.49" x2="2.34" y2="3.49" width="0.1016" layer="31"/>
<wire x1="2.25" y1="3.44" x2="2.25" y2="3.11" width="0.1016" layer="31"/>
<wire x1="2.345" y1="3.495" x2="2.345" y2="3.055" width="0.1016" layer="29"/>
<wire x1="2.345" y1="3.055" x2="2.155" y2="3.055" width="0.1016" layer="29"/>
<wire x1="2.155" y1="3.055" x2="2.155" y2="3.495" width="0.1016" layer="29"/>
<wire x1="2.155" y1="3.495" x2="2.345" y2="3.495" width="0.1016" layer="29"/>
<wire x1="2.25" y1="3.445" x2="2.25" y2="3.105" width="0.1016" layer="29"/>
<wire x1="1.84" y1="3.49" x2="1.84" y2="3.06" width="0.1016" layer="31"/>
<wire x1="1.84" y1="3.06" x2="1.66" y2="3.06" width="0.1016" layer="31"/>
<wire x1="1.66" y1="3.06" x2="1.66" y2="3.49" width="0.1016" layer="31"/>
<wire x1="1.66" y1="3.49" x2="1.84" y2="3.49" width="0.1016" layer="31"/>
<wire x1="1.75" y1="3.44" x2="1.75" y2="3.11" width="0.1016" layer="31"/>
<wire x1="1.845" y1="3.495" x2="1.845" y2="3.055" width="0.1016" layer="29"/>
<wire x1="1.845" y1="3.055" x2="1.655" y2="3.055" width="0.1016" layer="29"/>
<wire x1="1.655" y1="3.055" x2="1.655" y2="3.495" width="0.1016" layer="29"/>
<wire x1="1.655" y1="3.495" x2="1.845" y2="3.495" width="0.1016" layer="29"/>
<wire x1="1.75" y1="3.445" x2="1.75" y2="3.105" width="0.1016" layer="29"/>
<wire x1="1.34" y1="3.49" x2="1.34" y2="3.06" width="0.1016" layer="31"/>
<wire x1="1.34" y1="3.06" x2="1.16" y2="3.06" width="0.1016" layer="31"/>
<wire x1="1.16" y1="3.06" x2="1.16" y2="3.49" width="0.1016" layer="31"/>
<wire x1="1.16" y1="3.49" x2="1.34" y2="3.49" width="0.1016" layer="31"/>
<wire x1="1.25" y1="3.44" x2="1.25" y2="3.11" width="0.1016" layer="31"/>
<wire x1="1.345" y1="3.495" x2="1.345" y2="3.055" width="0.1016" layer="29"/>
<wire x1="1.345" y1="3.055" x2="1.155" y2="3.055" width="0.1016" layer="29"/>
<wire x1="1.155" y1="3.055" x2="1.155" y2="3.495" width="0.1016" layer="29"/>
<wire x1="1.155" y1="3.495" x2="1.345" y2="3.495" width="0.1016" layer="29"/>
<wire x1="1.25" y1="3.445" x2="1.25" y2="3.105" width="0.1016" layer="29"/>
<wire x1="0.84" y1="3.49" x2="0.84" y2="3.06" width="0.1016" layer="31"/>
<wire x1="0.84" y1="3.06" x2="0.66" y2="3.06" width="0.1016" layer="31"/>
<wire x1="0.66" y1="3.06" x2="0.66" y2="3.49" width="0.1016" layer="31"/>
<wire x1="0.66" y1="3.49" x2="0.84" y2="3.49" width="0.1016" layer="31"/>
<wire x1="0.75" y1="3.44" x2="0.75" y2="3.11" width="0.1016" layer="31"/>
<wire x1="0.845" y1="3.495" x2="0.845" y2="3.055" width="0.1016" layer="29"/>
<wire x1="0.845" y1="3.055" x2="0.655" y2="3.055" width="0.1016" layer="29"/>
<wire x1="0.655" y1="3.055" x2="0.655" y2="3.495" width="0.1016" layer="29"/>
<wire x1="0.655" y1="3.495" x2="0.845" y2="3.495" width="0.1016" layer="29"/>
<wire x1="0.75" y1="3.445" x2="0.75" y2="3.105" width="0.1016" layer="29"/>
<wire x1="0.34" y1="3.49" x2="0.34" y2="3.06" width="0.1016" layer="31"/>
<wire x1="0.34" y1="3.06" x2="0.16" y2="3.06" width="0.1016" layer="31"/>
<wire x1="0.16" y1="3.06" x2="0.16" y2="3.49" width="0.1016" layer="31"/>
<wire x1="0.16" y1="3.49" x2="0.34" y2="3.49" width="0.1016" layer="31"/>
<wire x1="0.25" y1="3.44" x2="0.25" y2="3.11" width="0.1016" layer="31"/>
<wire x1="0.345" y1="3.495" x2="0.345" y2="3.055" width="0.1016" layer="29"/>
<wire x1="0.345" y1="3.055" x2="0.155" y2="3.055" width="0.1016" layer="29"/>
<wire x1="0.155" y1="3.055" x2="0.155" y2="3.495" width="0.1016" layer="29"/>
<wire x1="0.155" y1="3.495" x2="0.345" y2="3.495" width="0.1016" layer="29"/>
<wire x1="0.25" y1="3.445" x2="0.25" y2="3.105" width="0.1016" layer="29"/>
<wire x1="-0.16" y1="3.49" x2="-0.16" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-0.16" y1="3.06" x2="-0.34" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-0.34" y1="3.06" x2="-0.34" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-0.34" y1="3.49" x2="-0.16" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-0.25" y1="3.44" x2="-0.25" y2="3.11" width="0.1016" layer="31"/>
<wire x1="-0.155" y1="3.495" x2="-0.155" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-0.155" y1="3.055" x2="-0.345" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-0.345" y1="3.055" x2="-0.345" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-0.345" y1="3.495" x2="-0.155" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-0.25" y1="3.445" x2="-0.25" y2="3.105" width="0.1016" layer="29"/>
<wire x1="-0.66" y1="3.49" x2="-0.66" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-0.66" y1="3.06" x2="-0.84" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-0.84" y1="3.06" x2="-0.84" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-0.84" y1="3.49" x2="-0.66" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-0.75" y1="3.44" x2="-0.75" y2="3.11" width="0.1016" layer="31"/>
<wire x1="-0.655" y1="3.495" x2="-0.655" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-0.655" y1="3.055" x2="-0.845" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-0.845" y1="3.055" x2="-0.845" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-0.845" y1="3.495" x2="-0.655" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-0.75" y1="3.445" x2="-0.75" y2="3.105" width="0.1016" layer="29"/>
<wire x1="-1.16" y1="3.49" x2="-1.16" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-1.16" y1="3.06" x2="-1.34" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-1.34" y1="3.06" x2="-1.34" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-1.34" y1="3.49" x2="-1.16" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-1.25" y1="3.44" x2="-1.25" y2="3.11" width="0.1016" layer="31"/>
<wire x1="-1.155" y1="3.495" x2="-1.155" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-1.155" y1="3.055" x2="-1.345" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-1.345" y1="3.055" x2="-1.345" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-1.345" y1="3.495" x2="-1.155" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-1.25" y1="3.445" x2="-1.25" y2="3.105" width="0.1016" layer="29"/>
<wire x1="-1.66" y1="3.49" x2="-1.66" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-1.66" y1="3.06" x2="-1.84" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-1.84" y1="3.06" x2="-1.84" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-1.84" y1="3.49" x2="-1.66" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-1.75" y1="3.44" x2="-1.75" y2="3.11" width="0.1016" layer="31"/>
<wire x1="-1.655" y1="3.495" x2="-1.655" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-1.655" y1="3.055" x2="-1.845" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-1.845" y1="3.055" x2="-1.845" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-1.845" y1="3.495" x2="-1.655" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-1.75" y1="3.445" x2="-1.75" y2="3.105" width="0.1016" layer="29"/>
<wire x1="-2.16" y1="3.49" x2="-2.16" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-2.16" y1="3.06" x2="-2.34" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-2.34" y1="3.06" x2="-2.34" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-2.34" y1="3.49" x2="-2.16" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-2.25" y1="3.44" x2="-2.25" y2="3.11" width="0.1016" layer="31"/>
<wire x1="-2.155" y1="3.495" x2="-2.155" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-2.155" y1="3.055" x2="-2.345" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-2.345" y1="3.055" x2="-2.345" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-2.345" y1="3.495" x2="-2.155" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-2.25" y1="3.445" x2="-2.25" y2="3.105" width="0.1016" layer="29"/>
<wire x1="-2.66" y1="3.49" x2="-2.66" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-2.66" y1="3.06" x2="-2.84" y2="3.06" width="0.1016" layer="31"/>
<wire x1="-2.84" y1="3.06" x2="-2.84" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-2.84" y1="3.49" x2="-2.66" y2="3.49" width="0.1016" layer="31"/>
<wire x1="-2.75" y1="3.44" x2="-2.75" y2="3.11" width="0.1016" layer="31"/>
<wire x1="-2.655" y1="3.495" x2="-2.655" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-2.655" y1="3.055" x2="-2.845" y2="3.055" width="0.1016" layer="29"/>
<wire x1="-2.845" y1="3.055" x2="-2.845" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-2.845" y1="3.495" x2="-2.655" y2="3.495" width="0.1016" layer="29"/>
<wire x1="-2.75" y1="3.445" x2="-2.75" y2="3.105" width="0.1016" layer="29"/>
<circle x="-3.115" y="2.75" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="2.25" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="1.75" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="1.25" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="0.75" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="0.25" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="-0.25" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="-0.75" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="-1.25" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="-1.75" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="-2.25" radius="0.1151" width="0" layer="51"/>
<circle x="-3.115" y="-2.75" radius="0.1151" width="0" layer="51"/>
<circle x="-2.75" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-2.25" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-1.75" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-1.25" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-0.75" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-0.25" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="0.25" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="0.75" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="1.25" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="1.75" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="2.25" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="2.75" y="-3.115" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="-2.75" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="-2.25" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="-1.75" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="-1.25" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="-0.75" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="-0.25" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="0.25" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="0.75" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="1.25" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="1.75" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="2.25" radius="0.1151" width="0" layer="51"/>
<circle x="3.115" y="2.75" radius="0.1151" width="0" layer="51"/>
<circle x="2.75" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="2.25" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="1.75" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="1.25" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="0.75" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="0.25" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-0.25" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-0.75" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-1.25" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-1.75" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-2.25" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-2.75" y="3.115" radius="0.1151" width="0" layer="51"/>
<circle x="-2.5" y="2.5" radius="0.4" width="0" layer="51"/>
<smd name="EXP" x="0" y="0" dx="5.3086" dy="5.3086" layer="1" roundness="5" stop="no" cream="no"/>
<smd name="1" x="-3.275" y="2.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="2" x="-3.275" y="2.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="3" x="-3.275" y="1.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="4" x="-3.275" y="1.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="5" x="-3.275" y="0.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="6" x="-3.275" y="0.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="7" x="-3.275" y="-0.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="8" x="-3.275" y="-0.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="9" x="-3.275" y="-1.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="10" x="-3.275" y="-1.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="11" x="-3.275" y="-2.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="12" x="-3.275" y="-2.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="13" x="-2.75" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="14" x="-2.25" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="15" x="-1.75" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="16" x="-1.25" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="17" x="-0.75" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="18" x="-0.25" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="19" x="0.25" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="20" x="0.75" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="21" x="1.25" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="22" x="1.75" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="23" x="2.25" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="24" x="2.75" y="-3.275" dx="0.3" dy="0.55" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="25" x="3.275" y="-2.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="26" x="3.275" y="-2.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="27" x="3.275" y="-1.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="28" x="3.275" y="-1.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="29" x="3.275" y="-0.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="30" x="3.275" y="-0.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="31" x="3.275" y="0.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="32" x="3.275" y="0.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="33" x="3.275" y="1.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="34" x="3.275" y="1.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="35" x="3.275" y="2.25" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="36" x="3.275" y="2.75" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="37" x="2.75" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="38" x="2.25" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="39" x="1.75" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="40" x="1.25" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="41" x="0.75" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="42" x="0.25" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="43" x="-0.25" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="44" x="-0.75" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="45" x="-1.25" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="46" x="-1.75" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="47" x="-2.25" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="48" x="-2.75" y="3.275" dx="0.3" dy="0.55" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<text x="-3" y="4" size="1" layer="25">&gt;NAME</text>
<text x="-3" y="-5" size="1" layer="27">&gt;VALUE</text>
<rectangle x1="-3.45" y1="2.535" x2="-3.22" y2="2.965" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="2.035" x2="-3.22" y2="2.465" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="1.535" x2="-3.22" y2="1.965" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="1.035" x2="-3.22" y2="1.465" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="0.535" x2="-3.22" y2="0.965" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="0.035" x2="-3.22" y2="0.465" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="-0.465" x2="-3.22" y2="-0.035" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="-0.965" x2="-3.22" y2="-0.535" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="-1.465" x2="-3.22" y2="-1.035" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="-1.965" x2="-3.22" y2="-1.535" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="-2.465" x2="-3.22" y2="-2.035" layer="51" rot="R270"/>
<rectangle x1="-3.45" y1="-2.965" x2="-3.22" y2="-2.535" layer="51" rot="R270"/>
<rectangle x1="-2.865" y1="-3.55" x2="-2.635" y2="-3.12" layer="51"/>
<rectangle x1="-2.365" y1="-3.55" x2="-2.135" y2="-3.12" layer="51"/>
<rectangle x1="-1.865" y1="-3.55" x2="-1.635" y2="-3.12" layer="51"/>
<rectangle x1="-1.365" y1="-3.55" x2="-1.135" y2="-3.12" layer="51"/>
<rectangle x1="-0.865" y1="-3.55" x2="-0.635" y2="-3.12" layer="51"/>
<rectangle x1="-0.365" y1="-3.55" x2="-0.135" y2="-3.12" layer="51"/>
<rectangle x1="0.135" y1="-3.55" x2="0.365" y2="-3.12" layer="51"/>
<rectangle x1="0.635" y1="-3.55" x2="0.865" y2="-3.12" layer="51"/>
<rectangle x1="1.135" y1="-3.55" x2="1.365" y2="-3.12" layer="51"/>
<rectangle x1="1.635" y1="-3.55" x2="1.865" y2="-3.12" layer="51"/>
<rectangle x1="2.135" y1="-3.55" x2="2.365" y2="-3.12" layer="51"/>
<rectangle x1="2.635" y1="-3.55" x2="2.865" y2="-3.12" layer="51"/>
<rectangle x1="3.22" y1="-2.965" x2="3.45" y2="-2.535" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="-2.465" x2="3.45" y2="-2.035" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="-1.965" x2="3.45" y2="-1.535" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="-1.465" x2="3.45" y2="-1.035" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="-0.965" x2="3.45" y2="-0.535" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="-0.465" x2="3.45" y2="-0.035" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="0.035" x2="3.45" y2="0.465" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="0.535" x2="3.45" y2="0.965" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="1.035" x2="3.45" y2="1.465" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="1.535" x2="3.45" y2="1.965" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="2.035" x2="3.45" y2="2.465" layer="51" rot="R90"/>
<rectangle x1="3.22" y1="2.535" x2="3.45" y2="2.965" layer="51" rot="R90"/>
<rectangle x1="2.635" y1="3.12" x2="2.865" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="2.135" y1="3.12" x2="2.365" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="1.635" y1="3.12" x2="1.865" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="1.135" y1="3.12" x2="1.365" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="0.635" y1="3.12" x2="0.865" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="0.135" y1="3.12" x2="0.365" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="-0.365" y1="3.12" x2="-0.135" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="-0.865" y1="3.12" x2="-0.635" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="-1.365" y1="3.12" x2="-1.135" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="-1.865" y1="3.12" x2="-1.635" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="-2.365" y1="3.12" x2="-2.135" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="-2.865" y1="3.12" x2="-2.635" y2="3.55" layer="51" rot="R180"/>
<rectangle x1="-2.54" y1="-2.54" x2="2.54" y2="2.54" layer="29"/>
<rectangle x1="-2.46" y1="-2.46" x2="2.46" y2="2.46" layer="31"/>
</package>
<package name="SOT-223">
<description>&lt;b&gt;SOT-223&lt;/b&gt;</description>
<wire x1="3.2766" y1="1.778" x2="3.2766" y2="-1.778" width="0.2032" layer="21"/>
<wire x1="3.2766" y1="-1.778" x2="-3.2766" y2="-1.778" width="0.2032" layer="21"/>
<wire x1="-3.2766" y1="-1.778" x2="-3.2766" y2="1.778" width="0.2032" layer="21"/>
<wire x1="-3.2766" y1="1.778" x2="3.2766" y2="1.778" width="0.2032" layer="21"/>
<smd name="1" x="-2.3114" y="-3.0988" dx="1.2192" dy="2.2352" layer="1"/>
<smd name="2" x="0" y="-3.0988" dx="1.2192" dy="2.2352" layer="1"/>
<smd name="3" x="2.3114" y="-3.0988" dx="1.2192" dy="2.2352" layer="1"/>
<smd name="4" x="0" y="3.099" dx="3.6" dy="2.2" layer="1"/>
<text x="-2.54" y="0.0508" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-1.3208" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.6002" y1="1.8034" x2="1.6002" y2="3.6576" layer="51"/>
<rectangle x1="-0.4318" y1="-3.6576" x2="0.4318" y2="-1.8034" layer="51"/>
<rectangle x1="-2.7432" y1="-3.6576" x2="-1.8796" y2="-1.8034" layer="51"/>
<rectangle x1="1.8796" y1="-3.6576" x2="2.7432" y2="-1.8034" layer="51"/>
<rectangle x1="-1.6002" y1="1.8034" x2="1.6002" y2="3.6576" layer="51"/>
<rectangle x1="-0.4318" y1="-3.6576" x2="0.4318" y2="-1.8034" layer="51"/>
<rectangle x1="-2.7432" y1="-3.6576" x2="-1.8796" y2="-1.8034" layer="51"/>
<rectangle x1="1.8796" y1="-3.6576" x2="2.7432" y2="-1.8034" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MK20D">
<pin name="VDD" x="-33.02" y="38.1" length="middle" direction="pwr"/>
<pin name="VDDA" x="-33.02" y="27.94" length="middle" direction="pwr"/>
<pin name="USB0_DP" x="-33.02" y="7.62" length="middle" direction="in"/>
<pin name="USB0_DM" x="-33.02" y="10.16" length="middle" direction="in"/>
<pin name="VREGIN" x="-33.02" y="43.18" length="middle" direction="in"/>
<pin name="VREFH" x="-33.02" y="25.4" length="middle" direction="in"/>
<pin name="VREFL" x="-33.02" y="17.78" length="middle" direction="in"/>
<pin name="RESET_B" x="-33.02" y="2.54" length="middle" direction="in"/>
<pin name="PTA0/SWD_CLK" x="-33.02" y="-10.16" length="middle"/>
<pin name="PTA1" x="-33.02" y="-12.7" length="middle"/>
<pin name="PTA2" x="-33.02" y="-15.24" length="middle"/>
<pin name="PTA3/SWD_DIO" x="-33.02" y="-17.78" length="middle"/>
<pin name="PTA4" x="-33.02" y="-20.32" length="middle"/>
<pin name="PTA18/EXTAL0" x="-33.02" y="-22.86" length="middle"/>
<pin name="PTA19/XTAL0" x="-33.02" y="-25.4" length="middle"/>
<pin name="VSS" x="-33.02" y="-30.48" length="middle" direction="pwr"/>
<pin name="VSSA" x="-33.02" y="15.24" length="middle" direction="in"/>
<pin name="LLWU_P/PTB0" x="33.02" y="-20.32" length="middle" rot="R180"/>
<pin name="PTB1" x="33.02" y="-17.78" length="middle" rot="R180"/>
<pin name="PTB2" x="33.02" y="-15.24" length="middle" rot="R180"/>
<pin name="PTB3" x="33.02" y="-12.7" length="middle" rot="R180"/>
<pin name="PTB16" x="33.02" y="-10.16" length="middle" rot="R180"/>
<pin name="PTB17" x="33.02" y="-7.62" length="middle" rot="R180"/>
<pin name="PTC0" x="33.02" y="0" length="middle" rot="R180"/>
<pin name="LLWU_P6/RTC_CL/PTC1" x="33.02" y="2.54" length="middle" rot="R180"/>
<pin name="PTC2" x="33.02" y="5.08" length="middle" rot="R180"/>
<pin name="LLWU_P7/PTC3" x="33.02" y="7.62" length="middle" rot="R180"/>
<pin name="LLWU_P8/PTC4" x="33.02" y="10.16" length="middle" rot="R180"/>
<pin name="LLWU_P9/PTC5" x="33.02" y="12.7" length="middle" rot="R180"/>
<pin name="LLWU_P10/PTC6" x="33.02" y="15.24" length="middle" rot="R180"/>
<pin name="PTC7" x="33.02" y="17.78" length="middle" rot="R180"/>
<pin name="PTD0" x="33.02" y="25.4" length="middle" rot="R180"/>
<pin name="PTD1" x="33.02" y="27.94" length="middle" rot="R180"/>
<pin name="PTD2" x="33.02" y="30.48" length="middle" rot="R180"/>
<pin name="PTD3" x="33.02" y="33.02" length="middle" rot="R180"/>
<pin name="LLWU_P14/PTD4" x="33.02" y="35.56" length="middle" rot="R180"/>
<pin name="PTD5" x="33.02" y="38.1" length="middle" rot="R180"/>
<pin name="LLWU_P15/PTD6" x="33.02" y="40.64" length="middle" rot="R180"/>
<pin name="PTD7" x="33.02" y="43.18" length="middle" rot="R180"/>
<pin name="VOUT33" x="-33.02" y="40.64" length="middle" direction="out"/>
<wire x1="-27.94" y1="48.26" x2="-27.94" y2="-35.56" width="0.4064" layer="94"/>
<wire x1="-27.94" y1="-35.56" x2="27.94" y2="-35.56" width="0.4064" layer="94"/>
<wire x1="27.94" y1="-35.56" x2="27.94" y2="48.26" width="0.4064" layer="94"/>
<wire x1="27.94" y1="48.26" x2="-27.94" y2="48.26" width="0.4064" layer="94"/>
<text x="-27.94" y="49.53" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-27.94" y="-39.37" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
<pin name="EXP" x="33.02" y="-33.02" length="middle" rot="R180"/>
<pin name="ADC0_DP0" x="-33.02" y="-2.54" length="middle" direction="in"/>
<pin name="ADC0_DM0" x="-33.02" y="-5.08" length="middle" direction="in"/>
<pin name="VREF_OUT" x="-33.02" y="22.86" length="middle" direction="out"/>
<pin name="XTAL32" x="33.02" y="-27.94" length="middle" rot="R180"/>
<pin name="EXTAL32" x="33.02" y="-25.4" length="middle" rot="R180"/>
<pin name="VBAT" x="-33.02" y="33.02" length="middle" direction="in"/>
</symbol>
<symbol name="VOLTAGE-REG">
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="2.54" width="0.4064" layer="94"/>
<wire x1="5.08" y1="2.54" x2="-5.08" y2="2.54" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<text x="2.54" y="-7.62" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.032" y="-4.318" size="1.524" layer="95">GND</text>
<text x="-4.445" y="-0.635" size="1.524" layer="95">IN</text>
<text x="0.635" y="-0.635" size="1.524" layer="95">OUT</text>
<pin name="IN" x="-7.62" y="0" visible="off" length="short" direction="in"/>
<pin name="GND" x="0" y="-7.62" visible="off" length="short" direction="in" rot="R90"/>
<pin name="OUT" x="7.62" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MK20D" prefix="IC">
<gates>
<gate name="G$1" symbol="MK20D" x="0" y="0"/>
</gates>
<devices>
<device name="FT" package="QFN48">
<connects>
<connect gate="G$1" pin="ADC0_DM0" pad="8"/>
<connect gate="G$1" pin="ADC0_DP0" pad="7"/>
<connect gate="G$1" pin="EXP" pad="EXP"/>
<connect gate="G$1" pin="EXTAL32" pad="15"/>
<connect gate="G$1" pin="LLWU_P/PTB0" pad="27"/>
<connect gate="G$1" pin="LLWU_P10/PTC6" pad="39"/>
<connect gate="G$1" pin="LLWU_P14/PTD4" pad="45"/>
<connect gate="G$1" pin="LLWU_P15/PTD6" pad="47"/>
<connect gate="G$1" pin="LLWU_P6/RTC_CL/PTC1" pad="34"/>
<connect gate="G$1" pin="LLWU_P7/PTC3" pad="36"/>
<connect gate="G$1" pin="LLWU_P8/PTC4" pad="37"/>
<connect gate="G$1" pin="LLWU_P9/PTC5" pad="38"/>
<connect gate="G$1" pin="PTA0/SWD_CLK" pad="17"/>
<connect gate="G$1" pin="PTA1" pad="18"/>
<connect gate="G$1" pin="PTA18/EXTAL0" pad="24"/>
<connect gate="G$1" pin="PTA19/XTAL0" pad="25"/>
<connect gate="G$1" pin="PTA2" pad="19"/>
<connect gate="G$1" pin="PTA3/SWD_DIO" pad="20"/>
<connect gate="G$1" pin="PTA4" pad="21"/>
<connect gate="G$1" pin="PTB1" pad="28"/>
<connect gate="G$1" pin="PTB16" pad="31"/>
<connect gate="G$1" pin="PTB17" pad="32"/>
<connect gate="G$1" pin="PTB2" pad="29"/>
<connect gate="G$1" pin="PTB3" pad="30"/>
<connect gate="G$1" pin="PTC0" pad="33"/>
<connect gate="G$1" pin="PTC2" pad="35"/>
<connect gate="G$1" pin="PTC7" pad="40"/>
<connect gate="G$1" pin="PTD0" pad="41"/>
<connect gate="G$1" pin="PTD1" pad="42"/>
<connect gate="G$1" pin="PTD2" pad="43"/>
<connect gate="G$1" pin="PTD3" pad="44"/>
<connect gate="G$1" pin="PTD5" pad="46"/>
<connect gate="G$1" pin="PTD7" pad="48"/>
<connect gate="G$1" pin="RESET_B" pad="26"/>
<connect gate="G$1" pin="USB0_DM" pad="4"/>
<connect gate="G$1" pin="USB0_DP" pad="3"/>
<connect gate="G$1" pin="VBAT" pad="16"/>
<connect gate="G$1" pin="VDD" pad="1 22"/>
<connect gate="G$1" pin="VDDA" pad="9"/>
<connect gate="G$1" pin="VOUT33" pad="5"/>
<connect gate="G$1" pin="VREFH" pad="10"/>
<connect gate="G$1" pin="VREFL" pad="11"/>
<connect gate="G$1" pin="VREF_OUT" pad="13"/>
<connect gate="G$1" pin="VREGIN" pad="6"/>
<connect gate="G$1" pin="VSS" pad="2 23"/>
<connect gate="G$1" pin="VSSA" pad="12"/>
<connect gate="G$1" pin="XTAL32" pad="14"/>
</connects>
<technologies>
<technology name="X128V?5"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="TC1262" prefix="IC">
<description>&lt;b&gt;500mA Fixed Output CMOS LDO&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="VOLTAGE-REG" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT-223">
<connects>
<connect gate="G$1" pin="GND" pad="2 4"/>
<connect gate="G$1" pin="IN" pad="1"/>
<connect gate="G$1" pin="OUT" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="74xx-little">
<packages>
<package name="SOT-353">
<description>&lt;b&gt;SOT-353&lt;/b&gt; (SC-88A, SC70-5)</description>
<wire x1="-1" y1="-0.55" x2="1" y2="-0.55" width="0.2032" layer="51"/>
<wire x1="1" y1="-0.55" x2="1" y2="0.55" width="0.2032" layer="21"/>
<wire x1="1" y1="0.55" x2="-1" y2="0.55" width="0.2032" layer="51"/>
<wire x1="-1" y1="0.55" x2="-1" y2="-0.55" width="0.2032" layer="21"/>
<smd name="2" x="0" y="-0.8" dx="0.4" dy="0.9" layer="1"/>
<smd name="1" x="-0.65" y="-0.8" dx="0.4" dy="0.9" layer="1"/>
<smd name="3" x="0.65" y="-0.8" dx="0.4" dy="0.9" layer="1"/>
<smd name="4" x="0.65" y="0.8" dx="0.4" dy="0.9" layer="1"/>
<smd name="5" x="-0.65" y="0.8" dx="0.4" dy="0.9" layer="1"/>
<text x="0" y="1.5" size="1" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.5" size="1" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-0.15" y1="-1.1" x2="0.15" y2="-0.65" layer="51"/>
<rectangle x1="-0.8" y1="-1.1" x2="-0.5" y2="-0.65" layer="51"/>
<rectangle x1="0.5" y1="-1.1" x2="0.8" y2="-0.65" layer="51"/>
<rectangle x1="0.5" y1="0.65" x2="0.8" y2="1.1" layer="51"/>
<rectangle x1="-0.8" y1="0.65" x2="-0.5" y2="1.1" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="74125">
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.4064" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="5.08" width="0.4064" layer="94"/>
<wire x1="0" y1="4.318" x2="0" y2="5.08" width="0.1524" layer="94"/>
<circle x="0" y="3.556" radius="0.762" width="0.1524" layer="94"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="OE" x="0" y="7.62" visible="pad" length="short" direction="in" rot="R270"/>
<pin name="I" x="-10.16" y="0" visible="pad" length="middle" direction="in"/>
<pin name="O" x="10.16" y="0" visible="pad" length="middle" direction="hiz" rot="R180"/>
</symbol>
<symbol name="PWRN">
<text x="-0.635" y="-0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.905" y="-6.35" size="1.27" layer="95" rot="R90">GND</text>
<text x="1.905" y="2.54" size="1.27" layer="95" rot="R90">VCC</text>
<pin name="GND" x="0" y="-7.62" visible="pad" length="middle" direction="pwr" rot="R90"/>
<pin name="VCC" x="0" y="7.62" visible="pad" length="middle" direction="pwr" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="74*1G125" prefix="IC">
<gates>
<gate name="G$1" symbol="74125" x="0" y="0"/>
<gate name="G$2" symbol="PWRN" x="-20.32" y="0" addlevel="request"/>
</gates>
<devices>
<device name="GW" package="SOT-353">
<connects>
<connect gate="G$1" pin="I" pad="2"/>
<connect gate="G$1" pin="O" pad="4"/>
<connect gate="G$1" pin="OE" pad="1"/>
<connect gate="G$2" pin="GND" pad="3"/>
<connect gate="G$2" pin="VCC" pad="5"/>
</connects>
<technologies>
<technology name="AHC"/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
<attribute name="DRAWN_BY" value="Christian Jost"/>
<attribute name="PROJECT" value="Infotronik"/>
<attribute name="REV" value="1.2"/>
<attribute name="TITLE" value="ucBoard K20"/>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME-A3" library="misc" deviceset="FRAME_A3L-DOC-HSLU" device=""/>
<part name="IC1" library="ICs" deviceset="MK20D" device="FT" technology="X128V?5"/>
<part name="X2" library="connectors" deviceset="MINI-USB-SHIELD" device="HIROSE-UX60SC-MB-5ST"/>
<part name="R1" library="passive" deviceset="R" device="0603" value="33"/>
<part name="R2" library="passive" deviceset="R" device="0603" value="33"/>
<part name="GND1" library="supply" deviceset="GND" device=""/>
<part name="+5V1" library="supply" deviceset="+5V" device=""/>
<part name="C1" library="passive" deviceset="C" device="0603" value="2u2"/>
<part name="Y2" library="discreteSemiconductors" deviceset="CSTCE" device="" technology="8M00G15C" value="8MHz"/>
<part name="GND4" library="supply" deviceset="GND" device=""/>
<part name="S1" library="misc" deviceset="KMR2*" device="" technology="11G-LFS" value="KMR2"/>
<part name="GND11" library="supply" deviceset="GND" device=""/>
<part name="X8" library="connectors" deviceset="STIFTLEISTE_2X5_1.27" device="-SMD"/>
<part name="GND30" library="supply" deviceset="GND" device=""/>
<part name="GND9" library="supply" deviceset="GND" device=""/>
<part name="GND10" library="supply" deviceset="GND" device=""/>
<part name="P1" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P2" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P3" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P4" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P5" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P6" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P7" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P8" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P9" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P10" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P11" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P12" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P13" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P14" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P15" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P16" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P17" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P18" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P19" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P20" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P21" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P22" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P25" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P26" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P27" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P28" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P29" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="L1" library="passive" deviceset="L" device=""/>
<part name="L2" library="passive" deviceset="L" device=""/>
<part name="L3" library="passive" deviceset="L" device=""/>
<part name="C5" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="C6" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="C7" library="passive" deviceset="C" device="0603" value="2u2"/>
<part name="R4" library="passive" deviceset="R" device="0603" value="470"/>
<part name="GND5" library="supply" deviceset="GND" device=""/>
<part name="D1" library="discreteSemiconductors" deviceset="BAS40-05" device="W"/>
<part name="D2" library="discreteSemiconductors" deviceset="BAS40-05" device="" value="BAS40-05"/>
<part name="D3" library="discreteSemiconductors" deviceset="VLM*" device="" technology="TG1300-GS08"/>
<part name="R7" library="passive" deviceset="R" device="0603" value="1k"/>
<part name="+3V2" library="supply" deviceset="+3V3" device=""/>
<part name="C8" library="passive" deviceset="C" device="0603" value="2u2"/>
<part name="C9" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="C10" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="GND12" library="supply" deviceset="GND" device=""/>
<part name="GND13" library="supply" deviceset="GND" device=""/>
<part name="GND14" library="supply" deviceset="GND" device=""/>
<part name="C11" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="GND15" library="supply" deviceset="GND" device=""/>
<part name="C12" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="GND16" library="supply" deviceset="GND" device=""/>
<part name="+3V3" library="supply" deviceset="+3V3" device=""/>
<part name="GND17" library="supply" deviceset="GND" device=""/>
<part name="P30" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P31" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P32" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P40" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P41" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="JP1" library="misc" deviceset="JP1" device="-SMD-1.2X1.8" value="JP1-SMD-1.2X1.8"/>
<part name="IC3" library="74xx-little" deviceset="74*1G125" device="GW" technology="AHC"/>
<part name="X3" library="connectors" deviceset="STIFTLEISTE_2X5_1.27" device="-SMD"/>
<part name="C13" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="GND6" library="supply" deviceset="GND" device=""/>
<part name="+3V1" library="supply" deviceset="+3V3" device=""/>
<part name="P33" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="F1" library="misc" deviceset="0603SFV*F/32-2" device="" technology="050"/>
<part name="P34" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P35" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P36" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="Y1" library="discreteSemiconductors" deviceset="AB?T" device="38" value="AB38T"/>
<part name="U$1" library="connectors" deviceset="USB-A" device="MOLEX_48037"/>
<part name="P23" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="+3V4" library="supply" deviceset="+3V3" device=""/>
<part name="+3V5" library="supply" deviceset="+3V3" device=""/>
<part name="R3" library="passive" deviceset="R" device="0603" value="1k"/>
<part name="R5" library="passive" deviceset="R" device="0603" value="10k"/>
<part name="C2" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="GND2" library="supply" deviceset="GND" device=""/>
<part name="+3V6" library="supply" deviceset="+3V3" device=""/>
<part name="X4" library="connectors" deviceset="MOLEX-MICRO-SD" device=""/>
<part name="C3" library="passive" deviceset="C" device="0603" value="2.2u"/>
<part name="+3V7" library="supply" deviceset="+3V3" device=""/>
<part name="GND3" library="supply" deviceset="GND" device=""/>
<part name="GND7" library="supply" deviceset="GND" device=""/>
<part name="IC2" library="ICs" deviceset="TC1262" device=""/>
<part name="GND8" library="supply" deviceset="GND" device=""/>
<part name="+3V8" library="supply" deviceset="+3V3" device=""/>
<part name="C4" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="C14" library="passive" deviceset="C" device="0603" value="100n"/>
<part name="GND18" library="supply" deviceset="GND" device=""/>
<part name="GND19" library="supply" deviceset="GND" device=""/>
<part name="JP3" library="misc" deviceset="JP1" device="-SMD-1.2X1.8" value="JP1-SMD-1.2X1.8"/>
<part name="JP4" library="misc" deviceset="JP1" device="-SMD-1.2X1.8" value="JP1-SMD-1.2X1.8"/>
<part name="P24" library="connectors" deviceset="SOLDERPAD" device=""/>
<part name="P37" library="connectors" deviceset="SOLDERPAD" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="10.16" y1="243.84" x2="107.95" y2="243.84" width="0.1524" layer="97" style="shortdash"/>
<wire x1="107.95" y1="243.84" x2="107.95" y2="195.58" width="0.1524" layer="97" style="shortdash"/>
<wire x1="107.95" y1="195.58" x2="10.16" y2="195.58" width="0.1524" layer="97" style="shortdash"/>
<wire x1="10.16" y1="195.58" x2="10.16" y2="243.84" width="0.1524" layer="97" style="shortdash"/>
<text x="26.67" y="196.85" size="1.778" layer="97">Debug-Interface</text>
<text x="279.4" y="249.555" size="1.778" layer="98">TGT SWD CLK</text>
<text x="279.4" y="241.935" size="1.778" layer="98">TGT SWD OE</text>
<text x="279.4" y="231.775" size="1.778" layer="98">TGT SWD DIO OUT</text>
<text x="279.4" y="221.615" size="1.778" layer="98">TGT SWD DIO IN</text>
<text x="279.4" y="183.515" size="1.778" layer="98">TGT RESET</text>
<wire x1="238.76" y1="50.8" x2="240.03" y2="52.07" width="0.1524" layer="98"/>
<wire x1="240.03" y1="52.07" x2="240.03" y2="49.53" width="0.1524" layer="98"/>
<wire x1="240.03" y1="49.53" x2="238.76" y2="50.8" width="0.1524" layer="98"/>
<wire x1="241.3" y1="54.61" x2="241.3" y2="52.07" width="0.1524" layer="98"/>
<wire x1="241.3" y1="52.07" x2="242.57" y2="53.34" width="0.1524" layer="98"/>
<wire x1="242.57" y1="53.34" x2="241.3" y2="54.61" width="0.1524" layer="98"/>
</plain>
<instances>
<instance part="FRAME-A3" gate="G$1" x="0" y="0"/>
<instance part="FRAME-A3" gate="G$2" x="383.54" y="3.81"/>
<instance part="IC1" gate="G$1" x="175.26" y="55.88"/>
<instance part="X2" gate="G" x="36.83" y="63.5" smashed="yes" rot="MR0">
<attribute name="PART" x="39.37" y="74.93" size="1.778" layer="95" font="vector" rot="MR0"/>
<attribute name="VALUE" x="22.86" y="80.01" size="1.778" layer="96" font="vector" rot="MR270"/>
</instance>
<instance part="X2" gate="S" x="36.83" y="53.34" smashed="yes" rot="MR0">
<attribute name="NAME" x="29.21" y="50.8" size="1.778" layer="95" font="vector" rot="MR0"/>
</instance>
<instance part="R1" gate="G$1" x="77.47" y="66.04" smashed="yes">
<attribute name="NAME" x="77.47" y="71.0946" size="1.778" layer="95" align="bottom-center"/>
<attribute name="VALUE" x="77.47" y="68.834" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="R2" gate="G$1" x="87.63" y="63.5" smashed="yes">
<attribute name="NAME" x="87.63" y="68.5546" size="1.778" layer="95" align="bottom-center"/>
<attribute name="VALUE" x="87.63" y="66.294" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="GND1" gate="1" x="64.77" y="48.26"/>
<instance part="+5V1" gate="G$1" x="64.77" y="149.86"/>
<instance part="C1" gate="G$1" x="64.77" y="59.69"/>
<instance part="Y2" gate="G$1" x="111.76" y="20.32"/>
<instance part="GND4" gate="1" x="111.76" y="10.16"/>
<instance part="S1" gate="G$1" x="53.34" y="205.74"/>
<instance part="GND11" gate="1" x="58.42" y="200.66"/>
<instance part="X8" gate="G$1" x="40.64" y="226.06"/>
<instance part="GND30" gate="1" x="30.48" y="213.36"/>
<instance part="GND9" gate="1" x="140.97" y="10.16"/>
<instance part="GND10" gate="1" x="209.55" y="10.16"/>
<instance part="P1" gate="G$1" x="231.14" y="99.06"/>
<instance part="P2" gate="G$1" x="231.14" y="96.52"/>
<instance part="P3" gate="G$1" x="231.14" y="93.98"/>
<instance part="P4" gate="G$1" x="231.14" y="91.44"/>
<instance part="P5" gate="G$1" x="231.14" y="88.9"/>
<instance part="P6" gate="G$1" x="231.14" y="86.36"/>
<instance part="P7" gate="G$1" x="231.14" y="83.82"/>
<instance part="P8" gate="G$1" x="231.14" y="81.28"/>
<instance part="P9" gate="G$1" x="231.14" y="73.66"/>
<instance part="P10" gate="G$1" x="231.14" y="71.12"/>
<instance part="P11" gate="G$1" x="231.14" y="68.58"/>
<instance part="P12" gate="G$1" x="231.14" y="66.04"/>
<instance part="P13" gate="G$1" x="231.14" y="63.5"/>
<instance part="P14" gate="G$1" x="231.14" y="60.96"/>
<instance part="P15" gate="G$1" x="231.14" y="58.42"/>
<instance part="P16" gate="G$1" x="231.14" y="55.88"/>
<instance part="P17" gate="G$1" x="231.14" y="48.26"/>
<instance part="P18" gate="G$1" x="231.14" y="45.72"/>
<instance part="P19" gate="G$1" x="231.14" y="43.18"/>
<instance part="P20" gate="G$1" x="231.14" y="40.64"/>
<instance part="P21" gate="G$1" x="231.14" y="38.1"/>
<instance part="P22" gate="G$1" x="231.14" y="35.56"/>
<instance part="P25" gate="G$1" x="135.89" y="53.34" rot="R180"/>
<instance part="P26" gate="G$1" x="135.89" y="50.8" rot="R180"/>
<instance part="P27" gate="G$1" x="135.89" y="43.18" rot="R180"/>
<instance part="P28" gate="G$1" x="135.89" y="40.64" rot="R180"/>
<instance part="P29" gate="G$1" x="135.89" y="35.56" rot="R180"/>
<instance part="L1" gate="G$1" x="34.29" y="35.56" rot="R90"/>
<instance part="L2" gate="G$1" x="114.3" y="96.52"/>
<instance part="L3" gate="G$1" x="90.17" y="71.12"/>
<instance part="C5" gate="G$1" x="104.14" y="76.2"/>
<instance part="C6" gate="G$1" x="132.08" y="74.93"/>
<instance part="C7" gate="G$1" x="96.52" y="78.74" smashed="yes">
<attribute name="NAME" x="92.71" y="80.01" size="1.778" layer="95"/>
<attribute name="VALUE" x="91.44" y="75.692" size="1.778" layer="96"/>
</instance>
<instance part="R4" gate="G$1" x="104.14" y="86.36" smashed="yes" rot="R90">
<attribute name="NAME" x="101.6" y="87.6046" size="1.778" layer="95" align="bottom-center"/>
<attribute name="VALUE" x="100.33" y="84.074" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="GND5" gate="1" x="82.55" y="71.12" rot="R270"/>
<instance part="D1" gate="G$1" x="102.87" y="58.42"/>
<instance part="D1" gate="G$2" x="102.87" y="53.34"/>
<instance part="D1" gate="G$3" x="105.41" y="55.88"/>
<instance part="D2" gate="G$1" x="142.24" y="135.89" rot="R270"/>
<instance part="D2" gate="G$2" x="137.16" y="135.89" smashed="yes" rot="R270"/>
<instance part="D2" gate="G$3" x="139.7" y="133.35" smashed="yes" rot="R270">
<attribute name="PART" x="134.62" y="139.065" size="1.778" layer="95" align="bottom-center"/>
<attribute name="VALUE" x="139.7" y="143.51" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="D3" gate="G$1" x="123.19" y="213.36"/>
<instance part="R7" gate="G$1" x="123.19" y="228.6" smashed="yes" rot="R90">
<attribute name="NAME" x="118.1354" y="228.6" size="1.778" layer="95" rot="R90" align="bottom-center"/>
<attribute name="VALUE" x="120.396" y="228.6" size="1.778" layer="96" rot="R90" align="bottom-center"/>
</instance>
<instance part="+3V2" gate="G$1" x="129.54" y="102.87"/>
<instance part="C8" gate="G$1" x="135.89" y="91.44" smashed="yes">
<attribute name="NAME" x="132.08" y="92.71" size="1.778" layer="95"/>
<attribute name="VALUE" x="130.81" y="88.392" size="1.778" layer="96"/>
</instance>
<instance part="C9" gate="G$1" x="129.54" y="91.44" smashed="yes">
<attribute name="NAME" x="125.73" y="92.71" size="1.778" layer="95"/>
<attribute name="VALUE" x="123.19" y="88.392" size="1.778" layer="96"/>
</instance>
<instance part="C10" gate="G$1" x="121.92" y="91.44" smashed="yes">
<attribute name="NAME" x="116.84" y="92.71" size="1.778" layer="95"/>
<attribute name="VALUE" x="114.3" y="88.392" size="1.778" layer="96"/>
</instance>
<instance part="GND12" gate="1" x="121.92" y="86.36"/>
<instance part="GND13" gate="1" x="129.54" y="86.36"/>
<instance part="GND14" gate="1" x="135.89" y="86.36"/>
<instance part="C11" gate="G$1" x="135.89" y="109.22" smashed="yes">
<attribute name="NAME" x="130.81" y="110.49" size="1.778" layer="95"/>
<attribute name="VALUE" x="128.27" y="106.172" size="1.778" layer="96"/>
</instance>
<instance part="GND15" gate="1" x="135.89" y="104.14"/>
<instance part="C12" gate="G$1" x="114.3" y="55.88"/>
<instance part="GND16" gate="1" x="114.3" y="50.8"/>
<instance part="+3V3" gate="G$1" x="96.52" y="60.96"/>
<instance part="GND17" gate="1" x="34.29" y="25.4"/>
<instance part="P30" gate="G$1" x="135.89" y="38.1" rot="R180"/>
<instance part="P31" gate="G$1" x="135.89" y="45.72" rot="R180"/>
<instance part="P32" gate="G$1" x="135.89" y="58.42" rot="R180"/>
<instance part="P40" gate="G$1" x="81.28" y="53.34" rot="R180"/>
<instance part="P41" gate="G$1" x="231.14" y="142.24"/>
<instance part="JP1" gate="A" x="93.98" y="144.78"/>
<instance part="JP1" gate="G$1" x="93.98" y="144.78"/>
<instance part="IC3" gate="G$1" x="314.96" y="231.14"/>
<instance part="IC3" gate="G$2" x="320.04" y="201.93"/>
<instance part="X3" gate="G$1" x="345.44" y="203.2"/>
<instance part="C13" gate="G$1" x="312.42" y="203.2" smashed="yes">
<attribute name="NAME" x="307.34" y="204.47" size="1.778" layer="95"/>
<attribute name="VALUE" x="304.8" y="200.152" size="1.778" layer="96"/>
</instance>
<instance part="GND6" gate="1" x="276.86" y="190.5"/>
<instance part="+3V1" gate="G$1" x="276.86" y="210.82"/>
<instance part="P33" gate="G$1" x="111.76" y="78.74" rot="R270"/>
<instance part="F1" gate="G$1" x="73.66" y="142.24"/>
<instance part="P34" gate="G$1" x="83.82" y="144.78" rot="R90"/>
<instance part="P35" gate="G$1" x="138.43" y="17.78" rot="R180"/>
<instance part="P36" gate="G$1" x="124.46" y="73.66" rot="R90"/>
<instance part="Y1" gate="G$1" x="232.41" y="29.21" rot="R90"/>
<instance part="U$1" gate="G$1" x="36.83" y="104.14" smashed="yes" rot="MR0">
<attribute name="NAME" x="35.56" y="109.728" size="1.778" layer="95" rot="MR0"/>
<attribute name="VALUE" x="24.638" y="92.71" size="1.778" layer="96" rot="MR90"/>
</instance>
<instance part="P23" gate="G$1" x="121.92" y="99.06" rot="R90"/>
<instance part="+3V4" gate="G$1" x="30.48" y="241.3"/>
<instance part="+3V5" gate="G$1" x="123.19" y="238.76"/>
<instance part="R3" gate="G$1" x="309.88" y="220.98" smashed="yes" rot="R180">
<attribute name="NAME" x="309.88" y="215.9254" size="1.778" layer="95" rot="R180" align="bottom-center"/>
<attribute name="VALUE" x="309.88" y="218.186" size="1.778" layer="96" rot="R180" align="bottom-center"/>
</instance>
<instance part="R5" gate="G$1" x="83.82" y="215.9" smashed="yes" rot="R270">
<attribute name="NAME" x="88.8746" y="215.9" size="1.778" layer="95" rot="R270" align="bottom-center"/>
<attribute name="VALUE" x="86.614" y="215.9" size="1.778" layer="96" rot="R270" align="bottom-center"/>
</instance>
<instance part="C2" gate="G$1" x="83.82" y="207.01"/>
<instance part="GND2" gate="1" x="83.82" y="201.93"/>
<instance part="+3V6" gate="G$1" x="83.82" y="223.52"/>
<instance part="X4" gate="G$1" x="347.98" y="101.6"/>
<instance part="C3" gate="G$1" x="327.66" y="124.46" smashed="yes">
<attribute name="NAME" x="322.58" y="125.73" size="1.778" layer="95"/>
<attribute name="VALUE" x="320.04" y="121.412" size="1.778" layer="96"/>
</instance>
<instance part="+3V7" gate="G$1" x="332.74" y="134.62"/>
<instance part="GND3" gate="1" x="327.66" y="119.38"/>
<instance part="GND7" gate="1" x="332.74" y="83.82"/>
<instance part="IC2" gate="G$1" x="171.45" y="124.46"/>
<instance part="GND8" gate="1" x="171.45" y="114.3"/>
<instance part="+3V8" gate="G$1" x="186.69" y="132.08"/>
<instance part="C4" gate="G$1" x="186.69" y="119.38" smashed="yes">
<attribute name="NAME" x="181.61" y="120.65" size="1.778" layer="95"/>
<attribute name="VALUE" x="179.07" y="116.332" size="1.778" layer="96"/>
</instance>
<instance part="C14" gate="G$1" x="160.02" y="119.38" smashed="yes">
<attribute name="NAME" x="154.94" y="120.65" size="1.778" layer="95"/>
<attribute name="VALUE" x="152.4" y="116.332" size="1.778" layer="96"/>
</instance>
<instance part="GND18" gate="1" x="160.02" y="114.3"/>
<instance part="GND19" gate="1" x="186.69" y="114.3"/>
<instance part="JP3" gate="A" x="246.38" y="58.42"/>
<instance part="JP4" gate="A" x="254" y="58.42"/>
<instance part="JP3" gate="G$1" x="246.38" y="58.42"/>
<instance part="JP4" gate="G$1" x="254" y="58.42"/>
<instance part="P24" gate="G$1" x="27.94" y="224.79" rot="R90"/>
<instance part="P37" gate="G$1" x="48.26" y="224.79" rot="R90"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="C1" gate="G$1" pin="2"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="64.77" y1="57.15" x2="64.77" y2="55.88" width="0.1524" layer="91"/>
<pinref part="X2" gate="G" pin="5"/>
<wire x1="64.77" y1="55.88" x2="64.77" y2="50.8" width="0.1524" layer="91"/>
<wire x1="41.91" y1="58.42" x2="41.91" y2="55.88" width="0.1524" layer="91"/>
<wire x1="41.91" y1="55.88" x2="49.53" y2="55.88" width="0.1524" layer="91"/>
<junction x="64.77" y="55.88"/>
<pinref part="U$1" gate="G$1" pin="4"/>
<wire x1="49.53" y1="55.88" x2="64.77" y2="55.88" width="0.1524" layer="91"/>
<wire x1="41.91" y1="101.6" x2="49.53" y2="101.6" width="0.1524" layer="91"/>
<wire x1="49.53" y1="101.6" x2="49.53" y2="55.88" width="0.1524" layer="91"/>
<junction x="49.53" y="55.88"/>
</segment>
<segment>
<pinref part="Y2" gate="G$1" pin="2"/>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="111.76" y1="12.7" x2="111.76" y2="15.24" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="S1" gate="G$1" pin="S"/>
<pinref part="GND11" gate="1" pin="GND"/>
<wire x1="58.42" y1="203.2" x2="58.42" y2="205.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="X8" gate="G$1" pin="3"/>
<wire x1="35.56" y1="229.87" x2="30.48" y2="229.87" width="0.1524" layer="91"/>
<wire x1="30.48" y1="229.87" x2="30.48" y2="226.06" width="0.1524" layer="91"/>
<pinref part="X8" gate="G$1" pin="5"/>
<wire x1="30.48" y1="226.06" x2="30.48" y2="218.44" width="0.1524" layer="91"/>
<wire x1="30.48" y1="218.44" x2="30.48" y2="215.9" width="0.1524" layer="91"/>
<wire x1="35.56" y1="226.06" x2="30.48" y2="226.06" width="0.1524" layer="91"/>
<junction x="30.48" y="226.06"/>
<pinref part="X8" gate="G$1" pin="9"/>
<wire x1="35.56" y1="218.44" x2="30.48" y2="218.44" width="0.1524" layer="91"/>
<junction x="30.48" y="218.44"/>
<pinref part="GND30" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="VSS"/>
<pinref part="GND9" gate="1" pin="GND"/>
<wire x1="142.24" y1="25.4" x2="140.97" y2="25.4" width="0.1524" layer="91"/>
<wire x1="140.97" y1="25.4" x2="140.97" y2="17.78" width="0.1524" layer="91"/>
<pinref part="P35" gate="G$1" pin="PAD"/>
<wire x1="140.97" y1="17.78" x2="140.97" y2="12.7" width="0.1524" layer="91"/>
<junction x="140.97" y="17.78"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="EXP"/>
<pinref part="GND10" gate="1" pin="GND"/>
<wire x1="208.28" y1="22.86" x2="209.55" y2="22.86" width="0.1524" layer="91"/>
<wire x1="209.55" y1="22.86" x2="209.55" y2="12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="L3" gate="G$1" pin="1"/>
<pinref part="GND5" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C10" gate="G$1" pin="2"/>
<pinref part="GND12" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C9" gate="G$1" pin="2"/>
<pinref part="GND13" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C8" gate="G$1" pin="2"/>
<pinref part="GND14" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C11" gate="G$1" pin="2"/>
<pinref part="GND15" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C12" gate="G$1" pin="2"/>
<pinref part="GND16" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="L1" gate="G$1" pin="1"/>
<pinref part="GND17" gate="1" pin="GND"/>
<wire x1="34.29" y1="27.94" x2="34.29" y2="30.48" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND6" gate="1" pin="GND"/>
<pinref part="X3" gate="G$1" pin="5"/>
<wire x1="340.36" y1="203.2" x2="337.82" y2="203.2" width="0.1524" layer="91"/>
<wire x1="337.82" y1="203.2" x2="337.82" y2="193.04" width="0.1524" layer="91"/>
<pinref part="C13" gate="G$1" pin="2"/>
<wire x1="337.82" y1="193.04" x2="320.04" y2="193.04" width="0.1524" layer="91"/>
<wire x1="320.04" y1="193.04" x2="312.42" y2="193.04" width="0.1524" layer="91"/>
<wire x1="312.42" y1="193.04" x2="312.42" y2="200.66" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$2" pin="GND"/>
<wire x1="320.04" y1="194.31" x2="320.04" y2="193.04" width="0.1524" layer="91"/>
<junction x="320.04" y="193.04"/>
<pinref part="X3" gate="G$1" pin="3"/>
<wire x1="340.36" y1="207.01" x2="337.82" y2="207.01" width="0.1524" layer="91"/>
<wire x1="337.82" y1="207.01" x2="337.82" y2="203.2" width="0.1524" layer="91"/>
<junction x="337.82" y="203.2"/>
<wire x1="312.42" y1="193.04" x2="276.86" y2="193.04" width="0.1524" layer="91"/>
<junction x="312.42" y="193.04"/>
</segment>
<segment>
<pinref part="C2" gate="G$1" pin="2"/>
<pinref part="GND2" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C3" gate="G$1" pin="2"/>
<pinref part="GND3" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="X4" gate="G$1" pin="VSS"/>
<pinref part="GND7" gate="1" pin="GND"/>
<wire x1="335.28" y1="91.44" x2="332.74" y2="91.44" width="0.1524" layer="91"/>
<wire x1="332.74" y1="91.44" x2="332.74" y2="86.36" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="GND"/>
<pinref part="GND8" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C14" gate="G$1" pin="2"/>
<pinref part="GND18" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C4" gate="G$1" pin="2"/>
<pinref part="GND19" gate="1" pin="GND"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="+5V1" gate="G$1" pin="+5V"/>
<wire x1="64.77" y1="142.24" x2="64.77" y2="147.32" width="0.1524" layer="91"/>
<junction x="64.77" y="142.24"/>
<pinref part="X2" gate="G" pin="1"/>
<wire x1="69.85" y1="142.24" x2="64.77" y2="142.24" width="0.1524" layer="91"/>
<wire x1="41.91" y1="68.58" x2="57.15" y2="68.58" width="0.1524" layer="91"/>
<wire x1="57.15" y1="68.58" x2="64.77" y2="68.58" width="0.1524" layer="91"/>
<wire x1="64.77" y1="68.58" x2="64.77" y2="142.24" width="0.1524" layer="91"/>
<junction x="64.77" y="68.58"/>
<pinref part="C1" gate="G$1" pin="1"/>
<wire x1="64.77" y1="62.23" x2="64.77" y2="68.58" width="0.1524" layer="91"/>
<pinref part="F1" gate="G$1" pin="1"/>
<pinref part="U$1" gate="G$1" pin="1"/>
<wire x1="41.91" y1="109.22" x2="57.15" y2="109.22" width="0.1524" layer="91"/>
<wire x1="57.15" y1="109.22" x2="57.15" y2="68.58" width="0.1524" layer="91"/>
<junction x="57.15" y="68.58"/>
</segment>
</net>
<net name="SWD_CLK" class="0">
<segment>
<pinref part="X8" gate="G$1" pin="4"/>
<label x="90.17" y="229.87" size="1.778" layer="95" xref="yes"/>
<wire x1="45.72" y1="229.87" x2="90.17" y2="229.87" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="PTA0/SWD_CLK"/>
<wire x1="142.24" y1="45.72" x2="138.43" y2="45.72" width="0.1524" layer="91"/>
<label x="111.76" y="44.45" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="P31" gate="G$1" pin="PAD"/>
<wire x1="138.43" y1="45.72" x2="138.43" y2="44.45" width="0.1524" layer="91"/>
<wire x1="138.43" y1="44.45" x2="111.76" y2="44.45" width="0.1524" layer="91"/>
<junction x="138.43" y="45.72"/>
</segment>
</net>
<net name="SWD_DIO" class="0">
<segment>
<pinref part="X8" gate="G$1" pin="2"/>
<wire x1="45.72" y1="233.68" x2="90.17" y2="233.68" width="0.1524" layer="91"/>
<label x="90.17" y="233.68" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="PTA3/SWD_DIO"/>
<wire x1="142.24" y1="38.1" x2="138.43" y2="38.1" width="0.1524" layer="91"/>
<label x="111.76" y="36.83" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="P30" gate="G$1" pin="PAD"/>
<wire x1="138.43" y1="38.1" x2="138.43" y2="36.83" width="0.1524" layer="91"/>
<wire x1="138.43" y1="36.83" x2="111.76" y2="36.83" width="0.1524" layer="91"/>
<junction x="138.43" y="38.1"/>
</segment>
</net>
<net name="RESET" class="0">
<segment>
<pinref part="S1" gate="G$1" pin="C"/>
<pinref part="X8" gate="G$1" pin="10"/>
<wire x1="45.72" y1="218.44" x2="48.26" y2="218.44" width="0.1524" layer="91"/>
<label x="90.17" y="210.82" size="1.778" layer="95" xref="yes"/>
<wire x1="48.26" y1="205.74" x2="48.26" y2="218.44" width="0.1524" layer="91"/>
<wire x1="48.26" y1="218.44" x2="77.47" y2="218.44" width="0.1524" layer="91"/>
<wire x1="77.47" y1="218.44" x2="77.47" y2="210.82" width="0.1524" layer="91"/>
<wire x1="77.47" y1="210.82" x2="83.82" y2="210.82" width="0.1524" layer="91"/>
<junction x="48.26" y="218.44"/>
<junction x="48.26" y="218.44"/>
<pinref part="R5" gate="G$1" pin="2"/>
<wire x1="83.82" y1="210.82" x2="90.17" y2="210.82" width="0.1524" layer="91"/>
<junction x="83.82" y="210.82"/>
<pinref part="C2" gate="G$1" pin="1"/>
<wire x1="83.82" y1="209.55" x2="83.82" y2="210.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="RESET_B"/>
<wire x1="142.24" y1="58.42" x2="138.43" y2="58.42" width="0.1524" layer="91"/>
<label x="128.27" y="60.96" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="P32" gate="G$1" pin="PAD"/>
<wire x1="138.43" y1="58.42" x2="138.43" y2="60.96" width="0.1524" layer="91"/>
<wire x1="138.43" y1="60.96" x2="128.27" y2="60.96" width="0.1524" layer="91"/>
<junction x="138.43" y="58.42"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="X2" gate="G" pin="2"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="41.91" y1="66.04" x2="54.61" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="2"/>
<wire x1="54.61" y1="66.04" x2="72.39" y2="66.04" width="0.1524" layer="91"/>
<wire x1="41.91" y1="106.68" x2="54.61" y2="106.68" width="0.1524" layer="91"/>
<wire x1="54.61" y1="106.68" x2="54.61" y2="66.04" width="0.1524" layer="91"/>
<junction x="54.61" y="66.04"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="X2" gate="G" pin="3"/>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="41.91" y1="63.5" x2="52.07" y2="63.5" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="3"/>
<wire x1="52.07" y1="63.5" x2="82.55" y2="63.5" width="0.1524" layer="91"/>
<wire x1="41.91" y1="104.14" x2="52.07" y2="104.14" width="0.1524" layer="91"/>
<wire x1="52.07" y1="104.14" x2="52.07" y2="63.5" width="0.1524" layer="91"/>
<junction x="52.07" y="63.5"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="2"/>
<pinref part="IC1" gate="G$1" pin="USB0_DM"/>
<wire x1="82.55" y1="66.04" x2="142.24" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="USB0_DP"/>
<pinref part="R2" gate="G$1" pin="2"/>
<wire x1="142.24" y1="63.5" x2="92.71" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="Y2" gate="G$1" pin="1"/>
<wire x1="109.22" y1="20.32" x2="101.6" y2="20.32" width="0.1524" layer="91"/>
<wire x1="101.6" y1="33.02" x2="101.6" y2="20.32" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PTA18/EXTAL0"/>
<wire x1="101.6" y1="33.02" x2="142.24" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="Y2" gate="G$1" pin="3"/>
<wire x1="114.3" y1="20.32" x2="121.92" y2="20.32" width="0.1524" layer="91"/>
<wire x1="142.24" y1="30.48" x2="121.92" y2="30.48" width="0.1524" layer="91"/>
<wire x1="121.92" y1="30.48" x2="121.92" y2="20.32" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PTA19/XTAL0"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="P1" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="PTD7"/>
<wire x1="228.6" y1="99.06" x2="208.28" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="LLWU_P15/PTD6"/>
<pinref part="P2" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="96.52" x2="228.6" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PTD5"/>
<pinref part="P3" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="93.98" x2="228.6" y2="93.98" width="0.1524" layer="91"/>
</segment>
</net>
<net name="LED" class="0">
<segment>
<pinref part="P4" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="LLWU_P14/PTD4"/>
<wire x1="228.6" y1="91.44" x2="223.52" y2="91.44" width="0.1524" layer="91"/>
<wire x1="223.52" y1="91.44" x2="208.28" y2="91.44" width="0.1524" layer="91"/>
<wire x1="223.52" y1="91.44" x2="223.52" y2="106.68" width="0.1524" layer="91"/>
<junction x="223.52" y="91.44"/>
<wire x1="223.52" y1="106.68" x2="231.14" y2="106.68" width="0.1524" layer="91"/>
<label x="231.14" y="106.68" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<label x="123.19" y="208.28" size="1.27" layer="95" rot="R270" xref="yes"/>
<pinref part="D3" gate="G$1" pin="K"/>
<wire x1="123.19" y1="208.28" x2="123.19" y2="210.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PTD3"/>
<pinref part="P5" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="88.9" x2="228.6" y2="88.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="P6" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="PTD2"/>
<wire x1="228.6" y1="86.36" x2="208.28" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PTD1"/>
<pinref part="P7" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="83.82" x2="228.6" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="P8" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="PTD0"/>
<wire x1="228.6" y1="81.28" x2="208.28" y2="81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="UART1_TX" class="0">
<segment>
<pinref part="X8" gate="G$1" pin="8"/>
<wire x1="45.72" y1="222.25" x2="48.26" y2="222.25" width="0.1524" layer="91"/>
<label x="50.8" y="222.25" size="1.778" layer="95" xref="yes"/>
<pinref part="P37" gate="G$1" pin="PAD"/>
<wire x1="48.26" y1="222.25" x2="50.8" y2="222.25" width="0.1524" layer="91"/>
<junction x="48.26" y="222.25"/>
</segment>
<segment>
<pinref part="X3" gate="G$1" pin="7"/>
<wire x1="340.36" y1="199.39" x2="332.74" y2="199.39" width="0.1524" layer="91"/>
<wire x1="332.74" y1="199.39" x2="332.74" y2="172.72" width="0.1524" layer="91"/>
<label x="332.74" y="172.72" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="248.92" y1="53.34" x2="261.62" y2="53.34" width="0.1524" layer="91"/>
<pinref part="JP3" gate="A" pin="2"/>
<wire x1="248.92" y1="55.88" x2="248.92" y2="53.34" width="0.1524" layer="91"/>
<label x="261.62" y="53.34" size="1.27" layer="95" xref="yes"/>
<pinref part="P12" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="LLWU_P8/PTC4"/>
<wire x1="228.6" y1="66.04" x2="218.44" y2="66.04" width="0.1524" layer="91"/>
<wire x1="218.44" y1="66.04" x2="208.28" y2="66.04" width="0.1524" layer="91"/>
<wire x1="218.44" y1="66.04" x2="218.44" y2="53.34" width="0.1524" layer="91"/>
<junction x="218.44" y="66.04"/>
<wire x1="218.44" y1="53.34" x2="246.38" y2="53.34" width="0.1524" layer="91"/>
<pinref part="JP3" gate="A" pin="1"/>
<wire x1="246.38" y1="55.88" x2="246.38" y2="53.34" width="0.1524" layer="91"/>
<wire x1="248.92" y1="53.34" x2="246.38" y2="53.34" width="0.1524" layer="91"/>
<junction x="248.92" y="53.34"/>
<junction x="246.38" y="53.34"/>
</segment>
</net>
<net name="UART1_RX" class="0">
<segment>
<pinref part="X8" gate="G$1" pin="7"/>
<wire x1="35.56" y1="222.25" x2="27.94" y2="222.25" width="0.1524" layer="91"/>
<label x="25.4" y="222.25" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="P24" gate="G$1" pin="PAD"/>
<wire x1="27.94" y1="222.25" x2="25.4" y2="222.25" width="0.1524" layer="91"/>
<junction x="27.94" y="222.25"/>
</segment>
<segment>
<pinref part="X3" gate="G$1" pin="8"/>
<wire x1="350.52" y1="199.39" x2="358.14" y2="199.39" width="0.1524" layer="91"/>
<wire x1="358.14" y1="199.39" x2="358.14" y2="172.72" width="0.1524" layer="91"/>
<label x="358.14" y="172.72" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="256.54" y1="50.8" x2="261.62" y2="50.8" width="0.1524" layer="91"/>
<pinref part="JP4" gate="A" pin="2"/>
<wire x1="256.54" y1="55.88" x2="256.54" y2="50.8" width="0.1524" layer="91"/>
<label x="261.62" y="50.8" size="1.27" layer="95" xref="yes"/>
<pinref part="IC1" gate="G$1" pin="LLWU_P7/PTC3"/>
<pinref part="P13" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="63.5" x2="215.9" y2="63.5" width="0.1524" layer="91"/>
<wire x1="215.9" y1="63.5" x2="228.6" y2="63.5" width="0.1524" layer="91"/>
<wire x1="215.9" y1="63.5" x2="215.9" y2="50.8" width="0.1524" layer="91"/>
<junction x="215.9" y="63.5"/>
<wire x1="215.9" y1="50.8" x2="254" y2="50.8" width="0.1524" layer="91"/>
<pinref part="JP4" gate="A" pin="1"/>
<wire x1="254" y1="55.88" x2="254" y2="50.8" width="0.1524" layer="91"/>
<wire x1="256.54" y1="50.8" x2="254" y2="50.8" width="0.1524" layer="91"/>
<junction x="256.54" y="50.8"/>
<junction x="254" y="50.8"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="P14" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="PTC2"/>
<wire x1="228.6" y1="60.96" x2="208.28" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PTC1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="LLWU_P6/RTC_CL/PTC1"/>
<pinref part="P15" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="58.42" x2="228.6" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="X4" gate="G$1" pin="CD/DAT3_(CS)"/>
<wire x1="335.28" y1="93.98" x2="322.58" y2="93.98" width="0.1524" layer="91"/>
<label x="322.58" y="93.98" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="PTC0" class="0">
<segment>
<pinref part="P16" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="PTC0"/>
<wire x1="228.6" y1="55.88" x2="208.28" y2="55.88" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="X4" gate="G$1" pin="SWITCH"/>
<wire x1="335.28" y1="109.22" x2="322.58" y2="109.22" width="0.1524" layer="91"/>
<label x="322.58" y="109.22" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PTB17"/>
<pinref part="P17" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="48.26" x2="228.6" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="P18" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="PTB16"/>
<wire x1="228.6" y1="45.72" x2="208.28" y2="45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PTB3"/>
<pinref part="P19" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="43.18" x2="228.6" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="P20" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="PTB2"/>
<wire x1="228.6" y1="40.64" x2="208.28" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$38" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="EXTAL32"/>
<wire x1="208.28" y1="30.48" x2="228.6" y2="30.48" width="0.1524" layer="91"/>
<pinref part="Y1" gate="G$1" pin="3"/>
<wire x1="232.41" y1="31.75" x2="228.6" y2="31.75" width="0.1524" layer="91"/>
<wire x1="228.6" y1="31.75" x2="228.6" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="XTAL32"/>
<wire x1="228.6" y1="27.94" x2="208.28" y2="27.94" width="0.1524" layer="91"/>
<pinref part="Y1" gate="G$1" pin="1"/>
<wire x1="232.41" y1="26.67" x2="228.6" y2="26.67" width="0.1524" layer="91"/>
<wire x1="228.6" y1="26.67" x2="228.6" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PTA4"/>
<pinref part="P29" gate="G$1" pin="PAD"/>
<wire x1="142.24" y1="35.56" x2="138.43" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="P28" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="PTA2"/>
<wire x1="138.43" y1="40.64" x2="142.24" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$42" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PTA1"/>
<wire x1="142.24" y1="43.18" x2="138.43" y2="43.18" width="0.1524" layer="91"/>
<pinref part="P27" gate="G$1" pin="PAD"/>
</segment>
</net>
<net name="N$43" class="0">
<segment>
<pinref part="P26" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="ADC0_DM0"/>
<wire x1="138.43" y1="50.8" x2="142.24" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$44" class="0">
<segment>
<pinref part="P25" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="ADC0_DP0"/>
<wire x1="138.43" y1="53.34" x2="142.24" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="VREFL"/>
<wire x1="142.24" y1="73.66" x2="140.97" y2="73.66" width="0.1524" layer="91"/>
<wire x1="140.97" y1="73.66" x2="140.97" y2="71.12" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="VSSA"/>
<wire x1="140.97" y1="71.12" x2="142.24" y2="71.12" width="0.1524" layer="91"/>
<pinref part="C6" gate="G$1" pin="2"/>
<wire x1="140.97" y1="71.12" x2="132.08" y2="71.12" width="0.1524" layer="91"/>
<wire x1="132.08" y1="71.12" x2="132.08" y2="72.39" width="0.1524" layer="91"/>
<junction x="140.97" y="71.12"/>
<pinref part="C5" gate="G$1" pin="2"/>
<wire x1="132.08" y1="71.12" x2="124.46" y2="71.12" width="0.1524" layer="91"/>
<wire x1="124.46" y1="71.12" x2="104.14" y2="71.12" width="0.1524" layer="91"/>
<wire x1="104.14" y1="71.12" x2="104.14" y2="73.66" width="0.1524" layer="91"/>
<junction x="132.08" y="71.12"/>
<pinref part="C7" gate="G$1" pin="2"/>
<wire x1="104.14" y1="71.12" x2="96.52" y2="71.12" width="0.1524" layer="91"/>
<wire x1="96.52" y1="71.12" x2="96.52" y2="76.2" width="0.1524" layer="91"/>
<junction x="104.14" y="71.12"/>
<pinref part="L3" gate="G$1" pin="2"/>
<wire x1="95.25" y1="71.12" x2="96.52" y2="71.12" width="0.1524" layer="91"/>
<junction x="96.52" y="71.12"/>
<pinref part="P36" gate="G$1" pin="PAD"/>
<junction x="124.46" y="71.12"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="VREF_OUT"/>
<pinref part="C6" gate="G$1" pin="1"/>
<wire x1="142.24" y1="78.74" x2="132.08" y2="78.74" width="0.1524" layer="91"/>
<wire x1="132.08" y1="78.74" x2="132.08" y2="77.47" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="VREFH"/>
<pinref part="C5" gate="G$1" pin="1"/>
<wire x1="142.24" y1="81.28" x2="111.76" y2="81.28" width="0.1524" layer="91"/>
<wire x1="111.76" y1="81.28" x2="104.14" y2="81.28" width="0.1524" layer="91"/>
<wire x1="104.14" y1="81.28" x2="104.14" y2="78.74" width="0.1524" layer="91"/>
<pinref part="R4" gate="G$1" pin="1"/>
<junction x="104.14" y="81.28"/>
<pinref part="P33" gate="G$1" pin="PAD"/>
<junction x="111.76" y="81.28"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="VREGIN"/>
<pinref part="D2" gate="G$3" pin="COMMON"/>
<wire x1="142.24" y1="99.06" x2="139.7" y2="99.06" width="0.1524" layer="91"/>
<wire x1="139.7" y1="99.06" x2="139.7" y2="114.3" width="0.1524" layer="91"/>
<pinref part="C11" gate="G$1" pin="1"/>
<wire x1="139.7" y1="114.3" x2="139.7" y2="124.46" width="0.1524" layer="91"/>
<wire x1="135.89" y1="111.76" x2="135.89" y2="114.3" width="0.1524" layer="91"/>
<wire x1="135.89" y1="114.3" x2="139.7" y2="114.3" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="IN"/>
<wire x1="139.7" y1="124.46" x2="160.02" y2="124.46" width="0.1524" layer="91"/>
<pinref part="C14" gate="G$1" pin="1"/>
<wire x1="160.02" y1="124.46" x2="163.83" y2="124.46" width="0.1524" layer="91"/>
<wire x1="160.02" y1="121.92" x2="160.02" y2="124.46" width="0.1524" layer="91"/>
<junction x="160.02" y="124.46"/>
<junction x="139.7" y="114.3"/>
<wire x1="139.7" y1="133.35" x2="139.7" y2="124.46" width="0.1524" layer="91"/>
<junction x="139.7" y="124.46"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="VOUT33"/>
<wire x1="142.24" y1="96.52" x2="139.7" y2="96.52" width="0.1524" layer="91"/>
<wire x1="139.7" y1="96.52" x2="139.7" y2="93.98" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="VDD"/>
<wire x1="139.7" y1="93.98" x2="142.24" y2="93.98" width="0.1524" layer="91"/>
<wire x1="139.7" y1="96.52" x2="135.89" y2="96.52" width="0.1524" layer="91"/>
<junction x="139.7" y="96.52"/>
<pinref part="L2" gate="G$1" pin="2"/>
<pinref part="C10" gate="G$1" pin="1"/>
<wire x1="135.89" y1="96.52" x2="129.54" y2="96.52" width="0.1524" layer="91"/>
<wire x1="129.54" y1="96.52" x2="121.92" y2="96.52" width="0.1524" layer="91"/>
<wire x1="121.92" y1="96.52" x2="119.38" y2="96.52" width="0.1524" layer="91"/>
<wire x1="121.92" y1="93.98" x2="121.92" y2="96.52" width="0.1524" layer="91"/>
<junction x="121.92" y="96.52"/>
<pinref part="C9" gate="G$1" pin="1"/>
<wire x1="129.54" y1="93.98" x2="129.54" y2="96.52" width="0.1524" layer="91"/>
<junction x="129.54" y="96.52"/>
<pinref part="C8" gate="G$1" pin="1"/>
<wire x1="135.89" y1="93.98" x2="135.89" y2="96.52" width="0.1524" layer="91"/>
<junction x="135.89" y="96.52"/>
<pinref part="+3V2" gate="G$1" pin="+3V3"/>
<wire x1="129.54" y1="100.33" x2="129.54" y2="96.52" width="0.1524" layer="91"/>
<pinref part="P23" gate="G$1" pin="PAD"/>
</segment>
<segment>
<pinref part="+3V3" gate="G$1" pin="+3V3"/>
<pinref part="D1" gate="G$1" pin="A"/>
<wire x1="96.52" y1="58.42" x2="100.33" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="304.8" y1="205.74" x2="276.86" y2="205.74" width="0.1524" layer="91"/>
<pinref part="+3V1" gate="G$1" pin="+3V3"/>
<wire x1="276.86" y1="205.74" x2="276.86" y2="208.28" width="0.1524" layer="91"/>
<pinref part="X3" gate="G$1" pin="1"/>
<pinref part="C13" gate="G$1" pin="1"/>
<wire x1="340.36" y1="210.82" x2="320.04" y2="210.82" width="0.1524" layer="91"/>
<wire x1="320.04" y1="210.82" x2="312.42" y2="210.82" width="0.1524" layer="91"/>
<wire x1="312.42" y1="210.82" x2="312.42" y2="205.74" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$2" pin="VCC"/>
<wire x1="320.04" y1="209.55" x2="320.04" y2="210.82" width="0.1524" layer="91"/>
<junction x="320.04" y="210.82"/>
<wire x1="304.8" y1="205.74" x2="304.8" y2="210.82" width="0.1524" layer="91"/>
<wire x1="304.8" y1="210.82" x2="312.42" y2="210.82" width="0.1524" layer="91"/>
<junction x="312.42" y="210.82"/>
</segment>
<segment>
<wire x1="30.48" y1="238.76" x2="30.48" y2="233.68" width="0.1524" layer="91"/>
<pinref part="X8" gate="G$1" pin="1"/>
<wire x1="30.48" y1="233.68" x2="35.56" y2="233.68" width="0.1524" layer="91"/>
<pinref part="+3V4" gate="G$1" pin="+3V3"/>
</segment>
<segment>
<pinref part="R7" gate="G$1" pin="2"/>
<pinref part="+3V5" gate="G$1" pin="+3V3"/>
<wire x1="123.19" y1="233.68" x2="123.19" y2="236.22" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R5" gate="G$1" pin="1"/>
<pinref part="+3V6" gate="G$1" pin="+3V3"/>
</segment>
<segment>
<pinref part="X4" gate="G$1" pin="VDD"/>
<pinref part="+3V7" gate="G$1" pin="+3V3"/>
<wire x1="335.28" y1="111.76" x2="332.74" y2="111.76" width="0.1524" layer="91"/>
<wire x1="332.74" y1="111.76" x2="332.74" y2="128.27" width="0.1524" layer="91"/>
<pinref part="C3" gate="G$1" pin="1"/>
<wire x1="332.74" y1="128.27" x2="332.74" y2="132.08" width="0.1524" layer="91"/>
<wire x1="332.74" y1="128.27" x2="327.66" y2="128.27" width="0.1524" layer="91"/>
<wire x1="327.66" y1="128.27" x2="327.66" y2="127" width="0.1524" layer="91"/>
<junction x="332.74" y="128.27"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="OUT"/>
<pinref part="+3V8" gate="G$1" pin="+3V3"/>
<wire x1="186.69" y1="129.54" x2="186.69" y2="124.46" width="0.1524" layer="91"/>
<wire x1="186.69" y1="124.46" x2="179.07" y2="124.46" width="0.1524" layer="91"/>
<pinref part="C4" gate="G$1" pin="1"/>
<wire x1="186.69" y1="121.92" x2="186.69" y2="124.46" width="0.1524" layer="91"/>
<junction x="186.69" y="124.46"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="C7" gate="G$1" pin="1"/>
<pinref part="L2" gate="G$1" pin="1"/>
<wire x1="109.22" y1="96.52" x2="107.95" y2="96.52" width="0.1524" layer="91"/>
<wire x1="107.95" y1="96.52" x2="104.14" y2="96.52" width="0.1524" layer="91"/>
<wire x1="104.14" y1="96.52" x2="96.52" y2="96.52" width="0.1524" layer="91"/>
<wire x1="96.52" y1="96.52" x2="96.52" y2="81.28" width="0.1524" layer="91"/>
<pinref part="R4" gate="G$1" pin="2"/>
<wire x1="104.14" y1="91.44" x2="104.14" y2="96.52" width="0.1524" layer="91"/>
<junction x="104.14" y="96.52"/>
<pinref part="IC1" gate="G$1" pin="VDDA"/>
<wire x1="142.24" y1="83.82" x2="107.95" y2="83.82" width="0.1524" layer="91"/>
<wire x1="107.95" y1="83.82" x2="107.95" y2="96.52" width="0.1524" layer="91"/>
<junction x="107.95" y="96.52"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="VBAT"/>
<wire x1="142.24" y1="88.9" x2="139.7" y2="88.9" width="0.1524" layer="91"/>
<wire x1="139.7" y1="88.9" x2="139.7" y2="80.01" width="0.1524" layer="91"/>
<wire x1="139.7" y1="80.01" x2="114.3" y2="80.01" width="0.1524" layer="91"/>
<wire x1="114.3" y1="80.01" x2="114.3" y2="60.96" width="0.1524" layer="91"/>
<wire x1="110.49" y1="60.96" x2="110.49" y2="55.88" width="0.1524" layer="91"/>
<pinref part="D1" gate="G$3" pin="COMMON"/>
<wire x1="110.49" y1="55.88" x2="105.41" y2="55.88" width="0.1524" layer="91"/>
<pinref part="C12" gate="G$1" pin="1"/>
<wire x1="114.3" y1="60.96" x2="110.49" y2="60.96" width="0.1524" layer="91"/>
<wire x1="114.3" y1="58.42" x2="114.3" y2="60.96" width="0.1524" layer="91"/>
<junction x="114.3" y="60.96"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="D1" gate="G$2" pin="A"/>
<wire x1="100.33" y1="53.34" x2="83.82" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P40" gate="G$1" pin="PAD"/>
</segment>
</net>
<net name="N$46" class="0">
<segment>
<pinref part="L1" gate="G$1" pin="2"/>
<wire x1="34.29" y1="40.64" x2="34.29" y2="44.45" width="0.1524" layer="91"/>
<pinref part="X2" gate="S" pin="S2"/>
<wire x1="31.75" y1="50.8" x2="31.75" y2="44.45" width="0.1524" layer="91"/>
<wire x1="31.75" y1="44.45" x2="34.29" y2="44.45" width="0.1524" layer="91"/>
<wire x1="34.29" y1="44.45" x2="46.99" y2="44.45" width="0.1524" layer="91"/>
<wire x1="46.99" y1="44.45" x2="46.99" y2="92.71" width="0.1524" layer="91"/>
<junction x="34.29" y="44.45"/>
<pinref part="U$1" gate="G$1" pin="S1"/>
<wire x1="46.99" y1="92.71" x2="39.37" y2="92.71" width="0.1524" layer="91"/>
<wire x1="39.37" y1="92.71" x2="39.37" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PTB0" class="0">
<segment>
<label x="276.86" y="241.3" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="IC3" gate="G$1" pin="OE"/>
<wire x1="314.96" y1="238.76" x2="314.96" y2="241.3" width="0.1524" layer="91"/>
<wire x1="314.96" y1="241.3" x2="276.86" y2="241.3" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="P22" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="LLWU_P/PTB0"/>
<wire x1="228.6" y1="35.56" x2="215.9" y2="35.56" width="0.1524" layer="91"/>
<wire x1="215.9" y1="35.56" x2="208.28" y2="35.56" width="0.1524" layer="91"/>
<wire x1="215.9" y1="35.56" x2="215.9" y2="20.32" width="0.1524" layer="91"/>
<junction x="215.9" y="35.56"/>
<wire x1="215.9" y1="20.32" x2="231.14" y2="20.32" width="0.1524" layer="91"/>
<label x="231.14" y="20.32" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="PTC6" class="0">
<segment>
<wire x1="304.8" y1="231.14" x2="276.86" y2="231.14" width="0.1524" layer="91"/>
<label x="276.86" y="231.14" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="IC3" gate="G$1" pin="I"/>
</segment>
<segment>
<pinref part="P10" gate="G$1" pin="PAD"/>
<pinref part="IC1" gate="G$1" pin="LLWU_P10/PTC6"/>
<wire x1="228.6" y1="71.12" x2="218.44" y2="71.12" width="0.1524" layer="91"/>
<wire x1="218.44" y1="71.12" x2="208.28" y2="71.12" width="0.1524" layer="91"/>
<wire x1="218.44" y1="71.12" x2="218.44" y2="111.76" width="0.1524" layer="91"/>
<junction x="218.44" y="71.12"/>
<wire x1="218.44" y1="111.76" x2="231.14" y2="111.76" width="0.1524" layer="91"/>
<label x="231.14" y="111.76" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="X4" gate="G$1" pin="CMD_(MOSI)"/>
<wire x1="335.28" y1="106.68" x2="322.58" y2="106.68" width="0.1524" layer="91"/>
<label x="322.58" y="106.68" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="PTC7" class="0">
<segment>
<label x="276.86" y="220.98" size="1.27" layer="95" rot="R180" xref="yes"/>
<wire x1="304.8" y1="220.98" x2="276.86" y2="220.98" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="PTC7"/>
<pinref part="P9" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="73.66" x2="220.98" y2="73.66" width="0.1524" layer="91"/>
<wire x1="220.98" y1="73.66" x2="228.6" y2="73.66" width="0.1524" layer="91"/>
<wire x1="220.98" y1="73.66" x2="220.98" y2="109.22" width="0.1524" layer="91"/>
<junction x="220.98" y="73.66"/>
<wire x1="220.98" y1="109.22" x2="231.14" y2="109.22" width="0.1524" layer="91"/>
<label x="231.14" y="109.22" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="X4" gate="G$1" pin="DAT0_(MISO)"/>
<wire x1="335.28" y1="101.6" x2="322.58" y2="101.6" width="0.1524" layer="91"/>
<label x="322.58" y="101.6" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="PTC5" class="0">
<segment>
<label x="276.86" y="248.92" size="1.27" layer="95" rot="R180" xref="yes"/>
<wire x1="358.14" y1="207.01" x2="358.14" y2="248.92" width="0.1524" layer="91"/>
<wire x1="358.14" y1="248.92" x2="276.86" y2="248.92" width="0.1524" layer="91"/>
<pinref part="X3" gate="G$1" pin="4"/>
<wire x1="358.14" y1="207.01" x2="350.52" y2="207.01" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="LLWU_P9/PTC5"/>
<pinref part="P11" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="68.58" x2="215.9" y2="68.58" width="0.1524" layer="91"/>
<wire x1="215.9" y1="68.58" x2="228.6" y2="68.58" width="0.1524" layer="91"/>
<wire x1="215.9" y1="68.58" x2="215.9" y2="114.3" width="0.1524" layer="91"/>
<junction x="215.9" y="68.58"/>
<wire x1="215.9" y1="114.3" x2="231.14" y2="114.3" width="0.1524" layer="91"/>
<label x="231.14" y="114.3" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="X4" gate="G$1" pin="CLK_(SCLK)"/>
<wire x1="335.28" y1="104.14" x2="322.58" y2="104.14" width="0.1524" layer="91"/>
<label x="322.58" y="104.14" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="PTB1" class="0">
<segment>
<label x="276.86" y="182.88" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="X3" gate="G$1" pin="10"/>
<wire x1="350.52" y1="195.58" x2="353.06" y2="195.58" width="0.1524" layer="91"/>
<wire x1="353.06" y1="195.58" x2="353.06" y2="182.88" width="0.1524" layer="91"/>
<wire x1="353.06" y1="182.88" x2="276.86" y2="182.88" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="PTB1"/>
<pinref part="P21" gate="G$1" pin="PAD"/>
<wire x1="208.28" y1="38.1" x2="218.44" y2="38.1" width="0.1524" layer="91"/>
<wire x1="218.44" y1="38.1" x2="228.6" y2="38.1" width="0.1524" layer="91"/>
<wire x1="218.44" y1="38.1" x2="218.44" y2="22.86" width="0.1524" layer="91"/>
<junction x="218.44" y="38.1"/>
<wire x1="218.44" y1="22.86" x2="231.14" y2="22.86" width="0.1524" layer="91"/>
<label x="231.14" y="22.86" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="R7" gate="G$1" pin="1"/>
<pinref part="D3" gate="G$1" pin="A"/>
<wire x1="123.19" y1="215.9" x2="123.19" y2="223.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="F1" gate="G$1" pin="2"/>
<pinref part="JP1" gate="A" pin="1"/>
<wire x1="93.98" y1="142.24" x2="83.82" y2="142.24" width="0.1524" layer="91"/>
<pinref part="P34" gate="G$1" pin="PAD"/>
<junction x="83.82" y="142.24"/>
<wire x1="83.82" y1="142.24" x2="77.47" y2="142.24" width="0.1524" layer="91"/>
<pinref part="D2" gate="G$1" pin="A"/>
<wire x1="142.24" y1="138.43" x2="142.24" y2="139.7" width="0.1524" layer="91"/>
<wire x1="142.24" y1="139.7" x2="139.7" y2="139.7" width="0.1524" layer="91"/>
<pinref part="D2" gate="G$2" pin="A"/>
<wire x1="139.7" y1="139.7" x2="137.16" y2="139.7" width="0.1524" layer="91"/>
<wire x1="137.16" y1="139.7" x2="137.16" y2="138.43" width="0.1524" layer="91"/>
<wire x1="139.7" y1="139.7" x2="139.7" y2="142.24" width="0.1524" layer="91"/>
<junction x="139.7" y="139.7"/>
<wire x1="139.7" y1="142.24" x2="96.52" y2="142.24" width="0.1524" layer="91"/>
<wire x1="139.7" y1="142.24" x2="228.6" y2="142.24" width="0.1524" layer="91"/>
<junction x="139.7" y="142.24"/>
<pinref part="P41" gate="G$1" pin="PAD"/>
<pinref part="JP1" gate="A" pin="2"/>
<wire x1="93.98" y1="142.24" x2="96.52" y2="142.24" width="0.1524" layer="91"/>
<junction x="93.98" y="142.24"/>
<junction x="96.52" y="142.24"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="X2" gate="S" pin="S1"/>
<wire x1="34.29" y1="50.8" x2="45.72" y2="50.8" width="0.1524" layer="91"/>
<wire x1="45.72" y1="50.8" x2="45.72" y2="91.44" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="S2"/>
<wire x1="45.72" y1="91.44" x2="36.83" y2="91.44" width="0.1524" layer="91"/>
<wire x1="36.83" y1="91.44" x2="36.83" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="O"/>
<wire x1="325.12" y1="231.14" x2="345.44" y2="231.14" width="0.1524" layer="91"/>
<wire x1="345.44" y1="231.14" x2="355.6" y2="231.14" width="0.1524" layer="91"/>
<wire x1="355.6" y1="231.14" x2="355.6" y2="210.82" width="0.1524" layer="91"/>
<pinref part="X3" gate="G$1" pin="2"/>
<wire x1="350.52" y1="210.82" x2="355.6" y2="210.82" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="1"/>
<wire x1="314.96" y1="220.98" x2="345.44" y2="220.98" width="0.1524" layer="91"/>
<wire x1="345.44" y1="220.98" x2="345.44" y2="231.14" width="0.1524" layer="91"/>
<junction x="345.44" y="231.14"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="104,1,83.82,111.76,U3,VDD_2,VCC,,,"/>
<approved hash="104,1,83.82,109.22,U3,VDD,VCC,,,"/>
<approved hash="104,1,83.82,106.68,U3,VDDA,VCC,,,"/>
<approved hash="104,1,83.82,43.18,U3,VSS_2,GND,,,"/>
<approved hash="104,1,83.82,40.64,U3,VSS,GND,,,"/>
<approved hash="104,1,248.92,109.22,U4,VS,N$12,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
