<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="yes" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="yes" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="yes" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="yes" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="yes" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="yes" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="yes" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="yes" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="yes" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="yes" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="yes" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="yes" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="yes" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="yes" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="yes" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="yes" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="yes" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="yes" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="yes" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="yes" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="yes" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="yes" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="yes" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="yes" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="yes" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="yes" active="no"/>
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
<library name="hslu_misc">
<packages>
<package name="MSOP10">
<description>&lt;b&gt;10-Lead Mini Small Outline Package [MSOP]&lt;/b&gt; (RM-10)&lt;p&gt;
Source: http://www.analog.com/UploadedFiles/Data_Sheets/35641221898805SSM2167_b.pdf&lt;br&gt;
COMPLIANT TO JEDEC STANDARDS MO-187BA</description>
<wire x1="-1.4" y1="1.4" x2="1.4" y2="1.4" width="0.2032" layer="21"/>
<wire x1="1.4" y1="1.4" x2="1.4" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="1.4" y1="-1.4" x2="-1.4" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="-1.4" y1="-1.4" x2="-1.4" y2="1.4" width="0.2032" layer="21"/>
<wire x1="-0.8" y1="-1.1" x2="-0.8" y2="-0.5" width="0.2032" layer="21" curve="-180"/>
<wire x1="-0.8" y1="-0.5" x2="-0.8" y2="-1.1" width="0.2032" layer="21"/>
<smd name="1" x="-1" y="-2.1131" dx="0.25" dy="1" layer="1"/>
<smd name="2" x="-0.5" y="-2.1131" dx="0.25" dy="1" layer="1"/>
<smd name="3" x="0" y="-2.1131" dx="0.25" dy="1" layer="1"/>
<smd name="4" x="0.5" y="-2.1131" dx="0.25" dy="1" layer="1"/>
<smd name="5" x="1" y="-2.1131" dx="0.25" dy="1" layer="1"/>
<smd name="6" x="1" y="2.1131" dx="0.25" dy="1" layer="1" rot="R180"/>
<smd name="7" x="0.5" y="2.1131" dx="0.25" dy="1" layer="1" rot="R180"/>
<smd name="8" x="0" y="2.1131" dx="0.25" dy="1" layer="1" rot="R180"/>
<smd name="9" x="-0.5" y="2.1131" dx="0.25" dy="1" layer="1" rot="R180"/>
<smd name="10" x="-1" y="2.1131" dx="0.25" dy="1" layer="1" rot="R180"/>
<text x="-2.032" y="0" size="1.016" layer="25" ratio="10" rot="R90" align="bottom-center">&gt;NAME</text>
<text x="3.302" y="0" size="1.016" layer="27" ratio="10" rot="R90" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-1.1244" y1="-2.5" x2="-0.8744" y2="-1.5" layer="51"/>
<rectangle x1="-0.6244" y1="-2.5" x2="-0.3744" y2="-1.5" layer="51"/>
<rectangle x1="-0.1244" y1="-2.5" x2="0.1256" y2="-1.5" layer="51"/>
<rectangle x1="0.3756" y1="-2.5" x2="0.6256" y2="-1.5" layer="51"/>
<rectangle x1="0.8756" y1="-2.5" x2="1.1256" y2="-1.5" layer="51"/>
<rectangle x1="0.8744" y1="1.5" x2="1.1244" y2="2.5" layer="51" rot="R180"/>
<rectangle x1="0.3744" y1="1.5" x2="0.6244" y2="2.5" layer="51" rot="R180"/>
<rectangle x1="-0.1256" y1="1.5" x2="0.1244" y2="2.5" layer="51" rot="R180"/>
<rectangle x1="-0.6256" y1="1.5" x2="-0.3756" y2="2.5" layer="51" rot="R180"/>
<rectangle x1="-1.1256" y1="1.5" x2="-0.8756" y2="2.5" layer="51" rot="R180"/>
</package>
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
<package name="SO14">
<description>&lt;b&gt;SMALL OUTLINE INTEGRATED CIRCUIT&lt;/b&gt;&lt;p&gt;
body 3.9 mm/JEDEC MS-012AC</description>
<wire x1="-4.895" y1="3.9" x2="4.895" y2="3.9" width="0.1998" layer="39"/>
<wire x1="4.895" y1="-3.9" x2="-4.895" y2="-3.9" width="0.1998" layer="39"/>
<wire x1="-4.895" y1="-3.9" x2="-4.895" y2="3.9" width="0.1998" layer="39"/>
<wire x1="4.305" y1="-1.9" x2="-4.305" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-4.305" y1="-1.9" x2="-4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-4.305" y1="-1.4" x2="-4.305" y2="1.9" width="0.2032" layer="51"/>
<wire x1="4.305" y1="-1.4" x2="-4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.305" y1="1.9" x2="4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.305" y1="-1.4" x2="4.305" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="4.895" y1="3.9" x2="4.895" y2="-3.9" width="0.1998" layer="39"/>
<wire x1="-4.305" y1="1.9" x2="4.305" y2="1.9" width="0.2032" layer="51"/>
<smd name="2" x="-2.54" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="13" x="-2.54" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-3.81" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="-1.27" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="0" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="14" x="-3.81" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="12" x="-1.27" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="11" x="0" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="2.54" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="9" x="2.54" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="1.27" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="3.81" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="10" x="1.27" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="3.81" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<text x="-5.08" y="0" size="1.27" layer="25" rot="R90" align="bottom-center">&gt;NAME</text>
<text x="6.35" y="0" size="1.27" layer="27" rot="R90" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-4.0551" y1="-3.1001" x2="-3.5649" y2="-2" layer="51"/>
<rectangle x1="-2.7851" y1="-3.1001" x2="-2.2949" y2="-2" layer="51"/>
<rectangle x1="-1.5151" y1="-3.1001" x2="-1.0249" y2="-2" layer="51"/>
<rectangle x1="-0.2451" y1="-3.1001" x2="0.2451" y2="-2" layer="51"/>
<rectangle x1="-0.2451" y1="2" x2="0.2451" y2="3.1001" layer="51"/>
<rectangle x1="-1.5151" y1="2" x2="-1.0249" y2="3.1001" layer="51"/>
<rectangle x1="-2.7851" y1="2" x2="-2.2949" y2="3.1001" layer="51"/>
<rectangle x1="-4.0551" y1="2" x2="-3.5649" y2="3.1001" layer="51"/>
<rectangle x1="1.0249" y1="-3.1001" x2="1.5151" y2="-2" layer="51"/>
<rectangle x1="2.2949" y1="-3.1001" x2="2.7851" y2="-2" layer="51"/>
<rectangle x1="3.5649" y1="-3.1001" x2="4.0551" y2="-2" layer="51"/>
<rectangle x1="3.5649" y1="2" x2="4.0551" y2="3.1001" layer="51"/>
<rectangle x1="2.2949" y1="2" x2="2.7851" y2="3.1001" layer="51"/>
<rectangle x1="1.0249" y1="2" x2="1.5151" y2="3.1001" layer="51"/>
</package>
<package name="TSSOP14">
<description>&lt;b&gt;plastic thin shrink small outline package; 14 leads; body width 4.4 mm&lt;/b&gt;&lt;p&gt;
SOT402-1&lt;br&gt;
Source: http://www.nxp.com/documents/data_sheet/74ABT125.pdf</description>
<wire x1="-2.45" y1="2.15" x2="2.45" y2="2.15" width="0.2032" layer="21"/>
<wire x1="2.45" y1="2.15" x2="2.45" y2="-2.15" width="0.2032" layer="21"/>
<wire x1="2.45" y1="-2.15" x2="-2.45" y2="-2.15" width="0.2032" layer="21"/>
<wire x1="-2.45" y1="-2.15" x2="-2.45" y2="2.15" width="0.2032" layer="21"/>
<circle x="-1.625" y="-1.3" radius="0.4596" width="0" layer="21"/>
<smd name="1" x="-1.95" y="-2.925" dx="0.35" dy="0.9" layer="1" stop="no"/>
<smd name="2" x="-1.3" y="-2.925" dx="0.35" dy="0.9" layer="1" stop="no"/>
<smd name="3" x="-0.65" y="-2.925" dx="0.35" dy="0.9" layer="1" stop="no"/>
<smd name="4" x="0" y="-2.925" dx="0.35" dy="0.9" layer="1" stop="no"/>
<smd name="5" x="0.65" y="-2.925" dx="0.35" dy="0.9" layer="1" stop="no"/>
<smd name="6" x="1.3" y="-2.925" dx="0.35" dy="0.9" layer="1" stop="no"/>
<smd name="7" x="1.95" y="-2.925" dx="0.35" dy="0.9" layer="1" stop="no"/>
<smd name="8" x="1.95" y="2.925" dx="0.35" dy="0.9" layer="1" rot="R180" stop="no"/>
<smd name="9" x="1.3" y="2.925" dx="0.35" dy="0.9" layer="1" rot="R180" stop="no"/>
<smd name="10" x="0.65" y="2.925" dx="0.35" dy="0.9" layer="1" rot="R180" stop="no"/>
<smd name="11" x="0" y="2.925" dx="0.35" dy="0.9" layer="1" rot="R180" stop="no"/>
<smd name="12" x="-0.65" y="2.925" dx="0.35" dy="0.9" layer="1" rot="R180" stop="no"/>
<smd name="13" x="-1.3" y="2.925" dx="0.35" dy="0.9" layer="1" rot="R180" stop="no"/>
<smd name="14" x="-1.95" y="2.925" dx="0.35" dy="0.9" layer="1" rot="R180" stop="no"/>
<text x="-2.667" y="0" size="1.27" layer="25" rot="R90" align="bottom-center">&gt;NAME</text>
<text x="3.937" y="0" size="1.27" layer="27" rot="R90" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-2.1" y1="-3.3" x2="-1.8" y2="-2.225" layer="51"/>
<rectangle x1="-1.45" y1="-3.3" x2="-1.15" y2="-2.225" layer="51"/>
<rectangle x1="-0.8" y1="-3.3" x2="-0.5" y2="-2.225" layer="51"/>
<rectangle x1="-0.15" y1="-3.3" x2="0.15" y2="-2.225" layer="51"/>
<rectangle x1="0.5" y1="-3.3" x2="0.8" y2="-2.225" layer="51"/>
<rectangle x1="1.15" y1="-3.3" x2="1.45" y2="-2.225" layer="51"/>
<rectangle x1="1.8" y1="-3.3" x2="2.1" y2="-2.225" layer="51"/>
<rectangle x1="1.8" y1="2.225" x2="2.1" y2="3.3" layer="51" rot="R180"/>
<rectangle x1="1.15" y1="2.225" x2="1.45" y2="3.3" layer="51" rot="R180"/>
<rectangle x1="0.5" y1="2.225" x2="0.8" y2="3.3" layer="51" rot="R180"/>
<rectangle x1="-0.15" y1="2.225" x2="0.15" y2="3.3" layer="51" rot="R180"/>
<rectangle x1="-0.8" y1="2.225" x2="-0.5" y2="3.3" layer="51" rot="R180"/>
<rectangle x1="-1.45" y1="2.225" x2="-1.15" y2="3.3" layer="51" rot="R180"/>
<rectangle x1="-2.1" y1="2.225" x2="-1.8" y2="3.3" layer="51" rot="R180"/>
<rectangle x1="-2.175" y1="-3.425" x2="-1.725" y2="-2.425" layer="29"/>
<rectangle x1="-1.525" y1="-3.425" x2="-1.075" y2="-2.425" layer="29"/>
<rectangle x1="-0.875" y1="-3.425" x2="-0.425" y2="-2.425" layer="29"/>
<rectangle x1="-0.225" y1="-3.425" x2="0.225" y2="-2.425" layer="29"/>
<rectangle x1="0.425" y1="-3.425" x2="0.875" y2="-2.425" layer="29"/>
<rectangle x1="1.075" y1="-3.425" x2="1.525" y2="-2.425" layer="29"/>
<rectangle x1="1.725" y1="-3.425" x2="2.175" y2="-2.425" layer="29"/>
<rectangle x1="1.725" y1="2.425" x2="2.175" y2="3.425" layer="29" rot="R180"/>
<rectangle x1="1.075" y1="2.425" x2="1.525" y2="3.425" layer="29" rot="R180"/>
<rectangle x1="0.425" y1="2.425" x2="0.875" y2="3.425" layer="29" rot="R180"/>
<rectangle x1="-0.225" y1="2.425" x2="0.225" y2="3.425" layer="29" rot="R180"/>
<rectangle x1="-0.875" y1="2.425" x2="-0.425" y2="3.425" layer="29" rot="R180"/>
<rectangle x1="-1.525" y1="2.425" x2="-1.075" y2="3.425" layer="29" rot="R180"/>
<rectangle x1="-2.175" y1="2.425" x2="-1.725" y2="3.425" layer="29" rot="R180"/>
</package>
<package name="PAD-R-10-20">
<pad name="1" x="0" y="0" drill="1" diameter="2"/>
<text x="1.778" y="0" size="1.27" layer="25" align="center-left">&gt;NAME</text>
<text x="1.778" y="-2.286" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="PAD_SMD_0603">
<text x="0" y="0.762" size="1.016" layer="25" font="vector" ratio="12" align="bottom-center">&gt;NAME</text>
<smd name="1" x="0.039" y="0" dx="2.794" dy="1" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="FRAME_A4L">
<frame x1="0" y1="0" x2="260.35" y2="179.07" columns="6" rows="4" layer="94"/>
</symbol>
<symbol name="DOCFIELD">
<wire x1="-104.14" y1="20.32" x2="-43.18" y2="20.32" width="0.1016" layer="94"/>
<text x="-40.64" y="15.24" size="3.556" layer="94" ratio="15">HSLU T&amp;A</text>
<text x="-40.64" y="1.905" size="1.778" layer="94">Technikumstrasse 21
CH-6048 Horw
http://www.hslu.ch
christian.jost@hslu.ch</text>
<wire x1="-43.18" y1="20.32" x2="0" y2="20.32" width="0.1016" layer="94"/>
<wire x1="-43.18" y1="20.32" x2="-43.18" y2="12.7" width="0.1016" layer="94"/>
<text x="-102.87" y="10.16" size="1.778" layer="94" align="center-left">Project:</text>
<text x="-102.87" y="5.08" size="1.778" layer="94" align="center-left">Date:</text>
<text x="-102.87" y="1.27" size="1.016" layer="94" align="center-left">$Id: QuadEncoder.sch 47 2014-02-12 09:02:14Z taalbiss $</text>
<text x="-63.5" y="10.16" size="1.778" layer="94" align="center-left">Rev.:</text>
<wire x1="-43.18" y1="12.7" x2="-43.18" y2="7.62" width="0.1016" layer="94"/>
<wire x1="-43.18" y1="7.62" x2="-43.18" y2="2.54" width="0.1016" layer="94"/>
<wire x1="-43.18" y1="2.54" x2="-43.18" y2="0" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="12.7" x2="-64.77" y2="12.7" width="0.1016" layer="94"/>
<wire x1="-64.77" y1="12.7" x2="-43.18" y2="12.7" width="0.1016" layer="94"/>
<wire x1="-43.18" y1="7.62" x2="-104.14" y2="7.62" width="0.1016" layer="94"/>
<text x="-63.5" y="5.08" size="1.778" layer="94" align="center-left">Sheet:</text>
<wire x1="-64.77" y1="12.7" x2="-64.77" y2="2.54" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="0" x2="-43.18" y2="0" width="0.1016" layer="94"/>
<wire x1="-43.18" y1="0" x2="0" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="20.32" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="20.32" x2="-104.14" y2="12.7" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="12.7" x2="-104.14" y2="7.62" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="7.62" x2="-104.14" y2="2.54" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="2.54" x2="-104.14" y2="0" width="0.1016" layer="94"/>
<wire x1="-104.14" y1="2.54" x2="-64.77" y2="2.54" width="0.1016" layer="94"/>
<wire x1="-64.77" y1="2.54" x2="-43.18" y2="2.54" width="0.1016" layer="94"/>
<text x="-53.34" y="5.08" size="1.778" layer="94" ratio="12" align="center-left">&gt;SHEET</text>
<text x="-93.98" y="5.08" size="1.778" layer="94" ratio="12" align="center-left">&gt;LAST_DATE_TIME</text>
</symbol>
<symbol name="MCP4728">
<wire x1="-10.16" y1="15.24" x2="10.16" y2="15.24" width="0.254" layer="94"/>
<wire x1="10.16" y1="15.24" x2="10.16" y2="-15.24" width="0.254" layer="94"/>
<wire x1="10.16" y1="-15.24" x2="-10.16" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-15.24" x2="-10.16" y2="15.24" width="0.254" layer="94"/>
<text x="-10.16" y="16.51" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="-17.78" size="1.778" layer="96">&gt;VALUE</text>
<pin name="SDA" x="-12.7" y="7.62" length="short" direction="in"/>
<pin name="!LDAC" x="-12.7" y="-2.54" length="short" direction="in"/>
<pin name="B" x="12.7" y="2.54" length="short" rot="R180"/>
<pin name="A" x="12.7" y="7.62" length="short" rot="R180"/>
<pin name="RDY/!BSY" x="-12.7" y="-7.62" length="short" direction="out"/>
<pin name="SCL" x="-12.7" y="2.54" length="short" direction="out"/>
<pin name="GND" x="12.7" y="-12.7" length="short" direction="pwr" rot="R180"/>
<pin name="VCC" x="12.7" y="12.7" length="short" direction="pwr" rot="R180"/>
<pin name="C" x="12.7" y="-2.54" length="short" rot="R180"/>
<pin name="D" x="12.7" y="-7.62" length="short" rot="R180"/>
</symbol>
<symbol name="OPAMP">
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.4064" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="3.175" x2="-3.81" y2="1.905" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="-2.54" x2="-3.175" y2="-2.54" width="0.1524" layer="94"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="IN-" x="-7.62" y="-2.54" visible="pad" length="short" direction="in"/>
<pin name="IN+" x="-7.62" y="2.54" visible="pad" length="short" direction="in"/>
<pin name="OUT" x="7.62" y="0" visible="pad" length="short" direction="out" rot="R180"/>
</symbol>
<symbol name="OPAMP-PWR">
<pin name="V+" x="0" y="7.62" visible="pad" length="middle" direction="pwr" rot="R270"/>
<pin name="V-" x="0" y="-7.62" visible="pad" length="middle" direction="pwr" rot="R90"/>
</symbol>
<symbol name="PAD">
<text x="5.08" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<text x="-1.016" y="1.524" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="0" y="0" visible="off" length="short" direction="pas"/>
<circle x="3.048" y="0" radius="0.567959375" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRAME_A4L-DOC">
<description>&lt;b&gt;FRAME&lt;/b&gt;
&lt;p&gt;
DIN A4, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="FRAME_A4L" x="0" y="0"/>
<gate name="G$2" symbol="DOCFIELD" x="256.54" y="3.81" addlevel="must"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MCP4728" prefix="IC">
<description>&lt;b&gt;12-Bit, Quad DAC with EEPROM Memory&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MCP4728" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MSOP10">
<connects>
<connect gate="G$1" pin="!LDAC" pad="4"/>
<connect gate="G$1" pin="A" pad="6"/>
<connect gate="G$1" pin="B" pad="7"/>
<connect gate="G$1" pin="C" pad="8"/>
<connect gate="G$1" pin="D" pad="9"/>
<connect gate="G$1" pin="GND" pad="10"/>
<connect gate="G$1" pin="RDY/!BSY" pad="5"/>
<connect gate="G$1" pin="SCL" pad="2"/>
<connect gate="G$1" pin="SDA" pad="3"/>
<connect gate="G$1" pin="VCC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MCP6004" prefix="IC">
<gates>
<gate name="A" symbol="OPAMP" x="-19.05" y="12.7" swaplevel="1"/>
<gate name="B" symbol="OPAMP" x="19.05" y="12.7" swaplevel="1"/>
<gate name="C" symbol="OPAMP" x="-19.05" y="-12.7" swaplevel="1"/>
<gate name="D" symbol="OPAMP" x="19.05" y="-12.7" swaplevel="1"/>
<gate name="G$5" symbol="OPAMP-PWR" x="-19.05" y="12.7" addlevel="request"/>
</gates>
<devices>
<device name="/P" package="DIL14">
<connects>
<connect gate="A" pin="IN+" pad="3"/>
<connect gate="A" pin="IN-" pad="2"/>
<connect gate="A" pin="OUT" pad="1"/>
<connect gate="B" pin="IN+" pad="5"/>
<connect gate="B" pin="IN-" pad="6"/>
<connect gate="B" pin="OUT" pad="7"/>
<connect gate="C" pin="IN+" pad="10"/>
<connect gate="C" pin="IN-" pad="9"/>
<connect gate="C" pin="OUT" pad="8"/>
<connect gate="D" pin="IN+" pad="12"/>
<connect gate="D" pin="IN-" pad="13"/>
<connect gate="D" pin="OUT" pad="14"/>
<connect gate="G$5" pin="V+" pad="4"/>
<connect gate="G$5" pin="V-" pad="11"/>
</connects>
<technologies>
<technology name="-E"/>
<technology name="-I"/>
</technologies>
</device>
<device name="/SL" package="SO14">
<connects>
<connect gate="A" pin="IN+" pad="3"/>
<connect gate="A" pin="IN-" pad="2"/>
<connect gate="A" pin="OUT" pad="1"/>
<connect gate="B" pin="IN+" pad="5"/>
<connect gate="B" pin="IN-" pad="6"/>
<connect gate="B" pin="OUT" pad="7"/>
<connect gate="C" pin="IN+" pad="10"/>
<connect gate="C" pin="IN-" pad="9"/>
<connect gate="C" pin="OUT" pad="8"/>
<connect gate="D" pin="IN+" pad="12"/>
<connect gate="D" pin="IN-" pad="13"/>
<connect gate="D" pin="OUT" pad="14"/>
<connect gate="G$5" pin="V+" pad="4"/>
<connect gate="G$5" pin="V-" pad="11"/>
</connects>
<technologies>
<technology name="-E"/>
<technology name="-I"/>
</technologies>
</device>
<device name="/ST" package="TSSOP14">
<connects>
<connect gate="A" pin="IN+" pad="3"/>
<connect gate="A" pin="IN-" pad="2"/>
<connect gate="A" pin="OUT" pad="1"/>
<connect gate="B" pin="IN+" pad="5"/>
<connect gate="B" pin="IN-" pad="6"/>
<connect gate="B" pin="OUT" pad="7"/>
<connect gate="C" pin="IN+" pad="10"/>
<connect gate="C" pin="IN-" pad="9"/>
<connect gate="C" pin="OUT" pad="8"/>
<connect gate="D" pin="IN+" pad="12"/>
<connect gate="D" pin="IN-" pad="13"/>
<connect gate="D" pin="OUT" pad="14"/>
<connect gate="G$5" pin="V+" pad="4"/>
<connect gate="G$5" pin="V-" pad="11"/>
</connects>
<technologies>
<technology name="-E"/>
<technology name="-I"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PAD" prefix="P">
<description>&lt;b&gt;Solderpad&lt;/b&gt;
&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="R-10-20" package="PAD-R-10-20">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD_0603" package="PAD_SMD_0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="passive">
<packages>
<package name="C0603-R">
<description>&lt;b&gt;Chip Capacitor 0603 reflow solder&lt;/b&gt;
&lt;p&gt;
Metric Code Size 1608</description>
<text x="0" y="1" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-0.725" y1="0.35" x2="0.725" y2="0.35" width="0.1016" layer="51"/>
<wire x1="0.725" y1="-0.35" x2="-0.725" y2="-0.35" width="0.1016" layer="51"/>
<smd name="1" x="-0.875" y="0" dx="1.05" dy="1.08" layer="1"/>
<smd name="2" x="0.875" y="0" dx="1.05" dy="1.08" layer="1"/>
<rectangle x1="-0.8" y1="-0.4" x2="-0.45" y2="0.4" layer="51"/>
<rectangle x1="0.45" y1="-0.4" x2="0.8" y2="0.4" layer="51"/>
</package>
<package name="C0805-R">
<description>&lt;b&gt;Chip Capacitor 0805 reflow solder&lt;/b&gt;
&lt;p&gt;
Metric Code Size 2012</description>
<wire x1="-0.925" y1="0.6" x2="0.925" y2="0.6" width="0.1016" layer="51"/>
<wire x1="0.925" y1="-0.6" x2="-0.925" y2="-0.6" width="0.1016" layer="51"/>
<smd name="1" x="-1" y="0" dx="1.3" dy="1.5" layer="1"/>
<smd name="2" x="1" y="0" dx="1.3" dy="1.5" layer="1"/>
<text x="0" y="1.25" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.25" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
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
<text x="0" y="1.25" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.25" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
<rectangle x1="-1" y1="-0.65" x2="-0.5" y2="0.65" layer="51"/>
<rectangle x1="0.5" y1="-0.65" x2="1" y2="0.65" layer="51"/>
</package>
<package name="R0603-R">
<description>&lt;b&gt;Chip Resistor 0603 reflow solder&lt;/b&gt;
&lt;p&gt;
Metric Code Size 1608</description>
<text x="0" y="1" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2" size="1.016" layer="27" align="bottom-center">&gt;VALUE</text>
<wire x1="-0.725" y1="0.35" x2="0.725" y2="0.35" width="0.1016" layer="51"/>
<wire x1="0.725" y1="-0.35" x2="-0.725" y2="-0.35" width="0.1016" layer="51"/>
<smd name="1" x="-0.875" y="0" dx="1.05" dy="1.08" layer="1"/>
<smd name="2" x="0.875" y="0" dx="1.05" dy="1.08" layer="1"/>
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
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;
&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.
&lt;p&gt;
Please keep in mind, that these devices are necessary for the automatic wiring of the supply signals.
&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.
&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.</description>
<packages>
</packages>
<symbols>
<symbol name="+3V3">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-1.905" y="-1.27" size="1.778" layer="96" rot="R90" align="bottom-center">&gt;VALUE</text>
<pin name="+3V3" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="0" y="-2.54" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
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
<part name="U$1" library="hslu_misc" deviceset="FRAME_A4L-DOC" device=""/>
<part name="IC1" library="hslu_misc" deviceset="MCP4728" device="">
<attribute name="DISTRIBUTOR" value="Mouser"/>
<attribute name="DISTRIBUTOR_NR" value="579-MCP4728-E/UN "/>
</part>
<part name="IC2" library="hslu_misc" deviceset="MCP6004" device="/ST" technology="-I" value="MCP6004-I/ST">
<attribute name="DISTRIBUTOR" value="Mouser"/>
<attribute name="DISTRIBUTOR_NR" value="579-MCP6004-I/ST"/>
</part>
<part name="C1" library="passive" deviceset="C" device="0805" value="100n"/>
<part name="R1" library="passive" deviceset="R" device="0805" value="3k3"/>
<part name="R2" library="passive" deviceset="R" device="0805" value="3k3"/>
<part name="R4" library="passive" deviceset="R" device="0805" value="100k"/>
<part name="R5" library="passive" deviceset="R" device="0805" value="3k3"/>
<part name="+3V1" library="supply" deviceset="+3V3" device=""/>
<part name="+3V2" library="supply" deviceset="+3V3" device=""/>
<part name="+3V3" library="supply" deviceset="+3V3" device=""/>
<part name="GND1" library="supply" deviceset="GND" device=""/>
<part name="GND2" library="supply" deviceset="GND" device=""/>
<part name="R3" library="passive" deviceset="R" device="0805" value="100k"/>
<part name="+3V4" library="supply" deviceset="+3V3" device=""/>
<part name="R6" library="passive" deviceset="R" device="0805" value="100k"/>
<part name="GND3" library="supply" deviceset="GND" device=""/>
<part name="R7" library="passive" deviceset="R" device="0805" value="3k3"/>
<part name="R8" library="passive" deviceset="R" device="0805" value="100k"/>
<part name="R9" library="passive" deviceset="R" device="0805" value="3k3"/>
<part name="R10" library="passive" deviceset="R" device="0805" value="100k"/>
<part name="R11" library="passive" deviceset="R" device="0805" value="3k3"/>
<part name="R12" library="passive" deviceset="R" device="0805" value="100k"/>
<part name="GND4" library="supply" deviceset="GND" device=""/>
<part name="C2" library="passive" deviceset="C" device="0805" value="100n"/>
<part name="C3" library="passive" deviceset="C" device="0805" value="100n"/>
<part name="C4" library="passive" deviceset="C" device="0805" value="100n"/>
<part name="GND5" library="supply" deviceset="GND" device=""/>
<part name="GND6" library="supply" deviceset="GND" device=""/>
<part name="GND7" library="supply" deviceset="GND" device=""/>
<part name="+3V5" library="supply" deviceset="+3V3" device=""/>
<part name="C5" library="passive" deviceset="C" device="0805" value="100n"/>
<part name="GND8" library="supply" deviceset="GND" device=""/>
<part name="GND9" library="supply" deviceset="GND" device=""/>
<part name="GND10" library="supply" deviceset="GND" device=""/>
<part name="+3V6" library="supply" deviceset="+3V3" device=""/>
<part name="+3V7" library="supply" deviceset="+3V3" device=""/>
<part name="C6" library="passive" deviceset="C" device="0805" value="100n"/>
<part name="GND11" library="supply" deviceset="GND" device=""/>
<part name="+3V8" library="supply" deviceset="+3V3" device=""/>
<part name="GND12" library="supply" deviceset="GND" device=""/>
<part name="P1" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P2" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P3" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P4" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P5" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P6" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P7" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P8" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P9" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P10" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P11" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P12" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P13" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P14" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P15" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P16" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P17" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
<part name="P18" library="hslu_misc" deviceset="PAD" device="SMD_0603" value="PADSMD_0603"/>
</parts>
<sheets>
<sheet>
<plain>
<text x="154.94" y="20.32" size="2.54" layer="94" ratio="12" align="center-left">QuadEncoder</text>
<text x="166.37" y="13.97" size="1.778" layer="94" ratio="12" align="center-left">Zumo-Intro</text>
<text x="201.93" y="13.97" size="1.778" layer="94" ratio="12" align="center-left">1.0</text>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="0" y="0"/>
<instance part="U$1" gate="G$2" x="256.54" y="3.81"/>
<instance part="IC1" gate="G$1" x="88.9" y="86.36">
<attribute name="DISTRIBUTOR" x="88.9" y="86.36" size="1.778" layer="96" display="off"/>
<attribute name="DISTRIBUTOR_NR" x="88.9" y="86.36" size="1.778" layer="96" display="off"/>
</instance>
<instance part="IC2" gate="A" x="203.2" y="63.5"/>
<instance part="IC2" gate="B" x="203.2" y="86.36">
<attribute name="DISTRIBUTOR" x="203.2" y="86.36" size="1.778" layer="96" display="off"/>
<attribute name="DISTRIBUTOR_NR" x="203.2" y="86.36" size="1.778" layer="96" display="off"/>
</instance>
<instance part="IC2" gate="C" x="203.2" y="116.84"/>
<instance part="IC2" gate="D" x="203.2" y="40.64"/>
<instance part="C1" gate="G$1" x="134.62" y="60.96"/>
<instance part="R1" gate="G$1" x="66.04" y="104.14" rot="R90"/>
<instance part="R2" gate="G$1" x="55.88" y="104.14" rot="R90"/>
<instance part="R4" gate="G$1" x="204.47" y="73.66"/>
<instance part="R5" gate="G$1" x="187.96" y="66.04"/>
<instance part="+3V1" gate="G$1" x="55.88" y="116.84"/>
<instance part="+3V2" gate="G$1" x="66.04" y="116.84"/>
<instance part="+3V3" gate="G$1" x="104.14" y="116.84"/>
<instance part="GND1" gate="1" x="106.68" y="63.5"/>
<instance part="GND2" gate="1" x="134.62" y="55.88"/>
<instance part="IC2" gate="G$5" x="203.2" y="116.84"/>
<instance part="R3" gate="G$1" x="45.72" y="104.14" rot="R90"/>
<instance part="+3V4" gate="G$1" x="45.72" y="116.84"/>
<instance part="R6" gate="G$1" x="55.88" y="71.12" rot="R90"/>
<instance part="GND3" gate="1" x="55.88" y="63.5"/>
<instance part="R7" gate="G$1" x="187.96" y="88.9"/>
<instance part="R8" gate="G$1" x="204.47" y="96.52"/>
<instance part="R9" gate="G$1" x="187.96" y="119.38"/>
<instance part="R10" gate="G$1" x="209.55" y="127"/>
<instance part="R11" gate="G$1" x="187.96" y="43.18"/>
<instance part="R12" gate="G$1" x="204.47" y="50.8"/>
<instance part="GND4" gate="1" x="203.2" y="106.68"/>
<instance part="C2" gate="G$1" x="134.62" y="83.82"/>
<instance part="C3" gate="G$1" x="134.62" y="114.3"/>
<instance part="C4" gate="G$1" x="134.62" y="38.1"/>
<instance part="GND5" gate="1" x="134.62" y="78.74"/>
<instance part="GND6" gate="1" x="134.62" y="109.22"/>
<instance part="GND7" gate="1" x="134.62" y="33.02"/>
<instance part="+3V5" gate="G$1" x="203.2" y="147.32"/>
<instance part="C5" gate="G$1" x="207.01" y="139.7"/>
<instance part="GND8" gate="1" x="207.01" y="134.62"/>
<instance part="GND9" gate="1" x="142.24" y="137.16"/>
<instance part="GND10" gate="1" x="165.1" y="137.16"/>
<instance part="+3V6" gate="G$1" x="157.48" y="137.16" rot="R180"/>
<instance part="+3V7" gate="G$1" x="180.34" y="137.16" rot="R180"/>
<instance part="C6" gate="G$1" x="109.22" y="107.95"/>
<instance part="GND11" gate="1" x="109.22" y="102.87"/>
<instance part="+3V8" gate="G$1" x="38.1" y="116.84"/>
<instance part="GND12" gate="1" x="38.1" y="63.5"/>
<instance part="P1" gate="G$1" x="33.02" y="99.06" rot="R180"/>
<instance part="P2" gate="G$1" x="33.02" y="93.98" rot="R180"/>
<instance part="P3" gate="G$1" x="33.02" y="88.9" rot="R180"/>
<instance part="P4" gate="G$1" x="33.02" y="83.82" rot="R180"/>
<instance part="P5" gate="G$1" x="33.02" y="78.74" rot="R180"/>
<instance part="P6" gate="G$1" x="33.02" y="73.66" rot="R180"/>
<instance part="P7" gate="G$1" x="142.24" y="142.24" rot="R90"/>
<instance part="P8" gate="G$1" x="170.18" y="142.24" rot="R90"/>
<instance part="P9" gate="G$1" x="152.4" y="142.24" rot="R90"/>
<instance part="P10" gate="G$1" x="157.48" y="142.24" rot="R90"/>
<instance part="P11" gate="G$1" x="165.1" y="142.24" rot="R90"/>
<instance part="P12" gate="G$1" x="147.32" y="142.24" rot="R90"/>
<instance part="P13" gate="G$1" x="175.26" y="142.24" rot="R90"/>
<instance part="P14" gate="G$1" x="180.34" y="142.24" rot="R90"/>
<instance part="P15" gate="G$1" x="233.68" y="63.5"/>
<instance part="P16" gate="G$1" x="233.68" y="86.36"/>
<instance part="P17" gate="G$1" x="233.68" y="116.84"/>
<instance part="P18" gate="G$1" x="233.68" y="40.64"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="SDA"/>
<wire x1="76.2" y1="93.98" x2="66.04" y2="93.98" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="66.04" y1="93.98" x2="33.02" y2="93.98" width="0.1524" layer="91"/>
<wire x1="66.04" y1="99.06" x2="66.04" y2="93.98" width="0.1524" layer="91"/>
<junction x="66.04" y="93.98"/>
<pinref part="P2" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="SCL"/>
<wire x1="76.2" y1="88.9" x2="55.88" y2="88.9" width="0.1524" layer="91"/>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="55.88" y1="88.9" x2="33.02" y2="88.9" width="0.1524" layer="91"/>
<wire x1="55.88" y1="99.06" x2="55.88" y2="88.9" width="0.1524" layer="91"/>
<junction x="55.88" y="88.9"/>
<pinref part="P3" gate="G$1" pin="1"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="GND"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="101.6" y1="73.66" x2="106.68" y2="73.66" width="0.1524" layer="91"/>
<wire x1="106.68" y1="73.66" x2="106.68" y2="66.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="2"/>
<pinref part="GND2" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="R6" gate="G$1" pin="1"/>
<pinref part="GND3" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="IC2" gate="G$5" pin="V-"/>
<pinref part="GND4" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C2" gate="G$1" pin="2"/>
<pinref part="GND5" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C3" gate="G$1" pin="2"/>
<pinref part="GND6" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C4" gate="G$1" pin="2"/>
<pinref part="GND7" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C5" gate="G$1" pin="2"/>
<pinref part="GND8" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="GND9" gate="1" pin="GND"/>
<wire x1="142.24" y1="139.7" x2="142.24" y2="142.24" width="0.1524" layer="91"/>
<pinref part="P7" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="GND10" gate="1" pin="GND"/>
<wire x1="165.1" y1="139.7" x2="165.1" y2="142.24" width="0.1524" layer="91"/>
<pinref part="P11" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="C6" gate="G$1" pin="2"/>
<pinref part="GND11" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="33.02" y1="73.66" x2="38.1" y2="73.66" width="0.1524" layer="91"/>
<wire x1="38.1" y1="73.66" x2="38.1" y2="66.04" width="0.1524" layer="91"/>
<pinref part="GND12" gate="1" pin="GND"/>
<pinref part="P6" gate="G$1" pin="1"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="2"/>
<pinref part="+3V2" gate="G$1" pin="+3V3"/>
<wire x1="66.04" y1="109.22" x2="66.04" y2="114.3" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="+3V1" gate="G$1" pin="+3V3"/>
<pinref part="R2" gate="G$1" pin="2"/>
<wire x1="55.88" y1="114.3" x2="55.88" y2="109.22" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="VCC"/>
<pinref part="+3V3" gate="G$1" pin="+3V3"/>
<wire x1="101.6" y1="99.06" x2="104.14" y2="99.06" width="0.1524" layer="91"/>
<wire x1="104.14" y1="99.06" x2="104.14" y2="110.49" width="0.1524" layer="91"/>
<pinref part="C6" gate="G$1" pin="1"/>
<wire x1="104.14" y1="110.49" x2="104.14" y2="114.3" width="0.1524" layer="91"/>
<wire x1="109.22" y1="110.49" x2="104.14" y2="110.49" width="0.1524" layer="91"/>
<junction x="104.14" y="110.49"/>
</segment>
<segment>
<pinref part="+3V5" gate="G$1" pin="+3V3"/>
<pinref part="IC2" gate="G$5" pin="V+"/>
<wire x1="203.2" y1="144.78" x2="203.2" y2="142.24" width="0.1524" layer="91"/>
<pinref part="C5" gate="G$1" pin="1"/>
<wire x1="203.2" y1="142.24" x2="203.2" y2="124.46" width="0.1524" layer="91"/>
<wire x1="203.2" y1="142.24" x2="207.01" y2="142.24" width="0.1524" layer="91"/>
<junction x="203.2" y="142.24"/>
</segment>
<segment>
<wire x1="157.48" y1="142.24" x2="157.48" y2="139.7" width="0.1524" layer="91"/>
<pinref part="+3V6" gate="G$1" pin="+3V3"/>
<pinref part="P10" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="180.34" y1="142.24" x2="180.34" y2="139.7" width="0.1524" layer="91"/>
<pinref part="+3V7" gate="G$1" pin="+3V3"/>
<pinref part="P14" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="33.02" y1="99.06" x2="38.1" y2="99.06" width="0.1524" layer="91"/>
<wire x1="38.1" y1="99.06" x2="38.1" y2="114.3" width="0.1524" layer="91"/>
<pinref part="+3V8" gate="G$1" pin="+3V3"/>
<pinref part="P1" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="R3" gate="G$1" pin="2"/>
<pinref part="+3V4" gate="G$1" pin="+3V3"/>
<wire x1="45.72" y1="109.22" x2="45.72" y2="114.3" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="!LDAC"/>
<wire x1="76.2" y1="83.82" x2="55.88" y2="83.82" width="0.1524" layer="91"/>
<pinref part="R6" gate="G$1" pin="2"/>
<wire x1="55.88" y1="83.82" x2="33.02" y2="83.82" width="0.1524" layer="91"/>
<wire x1="55.88" y1="76.2" x2="55.88" y2="83.82" width="0.1524" layer="91"/>
<junction x="55.88" y="83.82"/>
<pinref part="P4" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="RDY/!BSY"/>
<wire x1="76.2" y1="78.74" x2="45.72" y2="78.74" width="0.1524" layer="91"/>
<pinref part="P5" gate="G$1" pin="1"/>
<pinref part="R3" gate="G$1" pin="1"/>
<wire x1="45.72" y1="78.74" x2="33.02" y2="78.74" width="0.1524" layer="91"/>
<wire x1="45.72" y1="99.06" x2="45.72" y2="78.74" width="0.1524" layer="91"/>
<junction x="45.72" y="78.74"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="C1" gate="G$1" pin="1"/>
<wire x1="134.62" y1="66.04" x2="182.88" y2="66.04" width="0.1524" layer="91"/>
<wire x1="134.62" y1="63.5" x2="134.62" y2="66.04" width="0.1524" layer="91"/>
<pinref part="R5" gate="G$1" pin="1"/>
<wire x1="121.92" y1="66.04" x2="134.62" y2="66.04" width="0.1524" layer="91"/>
<junction x="134.62" y="66.04"/>
<pinref part="IC1" gate="G$1" pin="C"/>
<wire x1="101.6" y1="83.82" x2="121.92" y2="83.82" width="0.1524" layer="91"/>
<wire x1="121.92" y1="83.82" x2="121.92" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="IC2" gate="A" pin="IN-"/>
<wire x1="195.58" y1="60.96" x2="175.26" y2="60.96" width="0.1524" layer="91"/>
<wire x1="175.26" y1="60.96" x2="175.26" y2="142.24" width="0.1524" layer="91"/>
<pinref part="P13" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="IC2" gate="A" pin="OUT"/>
<wire x1="210.82" y1="63.5" x2="213.36" y2="63.5" width="0.1524" layer="91"/>
<pinref part="R4" gate="G$1" pin="2"/>
<wire x1="213.36" y1="63.5" x2="233.68" y2="63.5" width="0.1524" layer="91"/>
<wire x1="209.55" y1="73.66" x2="213.36" y2="73.66" width="0.1524" layer="91"/>
<wire x1="213.36" y1="73.66" x2="213.36" y2="63.5" width="0.1524" layer="91"/>
<junction x="213.36" y="63.5"/>
<pinref part="P15" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="IC2" gate="A" pin="IN+"/>
<wire x1="193.04" y1="66.04" x2="194.31" y2="66.04" width="0.1524" layer="91"/>
<pinref part="R5" gate="G$1" pin="2"/>
<pinref part="R4" gate="G$1" pin="1"/>
<wire x1="194.31" y1="66.04" x2="195.58" y2="66.04" width="0.1524" layer="91"/>
<wire x1="199.39" y1="73.66" x2="194.31" y2="73.66" width="0.1524" layer="91"/>
<wire x1="194.31" y1="73.66" x2="194.31" y2="66.04" width="0.1524" layer="91"/>
<junction x="194.31" y="66.04"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="R7" gate="G$1" pin="2"/>
<pinref part="IC2" gate="B" pin="IN+"/>
<wire x1="193.04" y1="88.9" x2="194.31" y2="88.9" width="0.1524" layer="91"/>
<wire x1="194.31" y1="88.9" x2="195.58" y2="88.9" width="0.1524" layer="91"/>
<wire x1="194.31" y1="88.9" x2="194.31" y2="96.52" width="0.1524" layer="91"/>
<junction x="194.31" y="88.9"/>
<pinref part="R8" gate="G$1" pin="1"/>
<wire x1="194.31" y1="96.52" x2="199.39" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="IC2" gate="B" pin="OUT"/>
<wire x1="210.82" y1="86.36" x2="213.36" y2="86.36" width="0.1524" layer="91"/>
<pinref part="R8" gate="G$1" pin="2"/>
<wire x1="213.36" y1="86.36" x2="233.68" y2="86.36" width="0.1524" layer="91"/>
<wire x1="209.55" y1="96.52" x2="213.36" y2="96.52" width="0.1524" layer="91"/>
<wire x1="213.36" y1="96.52" x2="213.36" y2="86.36" width="0.1524" layer="91"/>
<junction x="213.36" y="86.36"/>
<pinref part="P16" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="IC2" gate="B" pin="IN-"/>
<wire x1="195.58" y1="83.82" x2="147.32" y2="83.82" width="0.1524" layer="91"/>
<wire x1="147.32" y1="83.82" x2="147.32" y2="142.24" width="0.1524" layer="91"/>
<pinref part="P12" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="R7" gate="G$1" pin="1"/>
<pinref part="C2" gate="G$1" pin="1"/>
<wire x1="134.62" y1="88.9" x2="182.88" y2="88.9" width="0.1524" layer="91"/>
<wire x1="134.62" y1="86.36" x2="134.62" y2="88.9" width="0.1524" layer="91"/>
<junction x="134.62" y="88.9"/>
<pinref part="IC1" gate="G$1" pin="B"/>
<wire x1="101.6" y1="88.9" x2="134.62" y2="88.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="R9" gate="G$1" pin="2"/>
<wire x1="193.04" y1="119.38" x2="194.31" y2="119.38" width="0.1524" layer="91"/>
<wire x1="194.31" y1="119.38" x2="195.58" y2="119.38" width="0.1524" layer="91"/>
<wire x1="194.31" y1="119.38" x2="194.31" y2="127" width="0.1524" layer="91"/>
<junction x="194.31" y="119.38"/>
<pinref part="R10" gate="G$1" pin="1"/>
<wire x1="194.31" y1="127" x2="204.47" y2="127" width="0.1524" layer="91"/>
<pinref part="IC2" gate="C" pin="IN+"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<wire x1="210.82" y1="116.84" x2="215.9" y2="116.84" width="0.1524" layer="91"/>
<pinref part="R10" gate="G$1" pin="2"/>
<wire x1="215.9" y1="116.84" x2="233.68" y2="116.84" width="0.1524" layer="91"/>
<wire x1="214.63" y1="127" x2="215.9" y2="127" width="0.1524" layer="91"/>
<wire x1="215.9" y1="127" x2="215.9" y2="116.84" width="0.1524" layer="91"/>
<junction x="215.9" y="116.84"/>
<pinref part="IC2" gate="C" pin="OUT"/>
<pinref part="P17" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<wire x1="195.58" y1="114.3" x2="152.4" y2="114.3" width="0.1524" layer="91"/>
<wire x1="152.4" y1="114.3" x2="152.4" y2="142.24" width="0.1524" layer="91"/>
<pinref part="IC2" gate="C" pin="IN-"/>
<pinref part="P9" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="R9" gate="G$1" pin="1"/>
<wire x1="134.62" y1="119.38" x2="182.88" y2="119.38" width="0.1524" layer="91"/>
<pinref part="C3" gate="G$1" pin="1"/>
<wire x1="134.62" y1="116.84" x2="134.62" y2="119.38" width="0.1524" layer="91"/>
<junction x="134.62" y="119.38"/>
<pinref part="IC1" gate="G$1" pin="A"/>
<wire x1="101.6" y1="93.98" x2="121.92" y2="93.98" width="0.1524" layer="91"/>
<wire x1="121.92" y1="93.98" x2="121.92" y2="119.38" width="0.1524" layer="91"/>
<wire x1="121.92" y1="119.38" x2="134.62" y2="119.38" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="R11" gate="G$1" pin="2"/>
<wire x1="193.04" y1="43.18" x2="194.31" y2="43.18" width="0.1524" layer="91"/>
<wire x1="194.31" y1="43.18" x2="195.58" y2="43.18" width="0.1524" layer="91"/>
<wire x1="194.31" y1="43.18" x2="194.31" y2="50.8" width="0.1524" layer="91"/>
<junction x="194.31" y="43.18"/>
<pinref part="R12" gate="G$1" pin="1"/>
<wire x1="194.31" y1="50.8" x2="199.39" y2="50.8" width="0.1524" layer="91"/>
<pinref part="IC2" gate="D" pin="IN+"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<wire x1="210.82" y1="40.64" x2="213.36" y2="40.64" width="0.1524" layer="91"/>
<pinref part="R12" gate="G$1" pin="2"/>
<wire x1="213.36" y1="40.64" x2="233.68" y2="40.64" width="0.1524" layer="91"/>
<wire x1="209.55" y1="50.8" x2="213.36" y2="50.8" width="0.1524" layer="91"/>
<wire x1="213.36" y1="50.8" x2="213.36" y2="40.64" width="0.1524" layer="91"/>
<junction x="213.36" y="40.64"/>
<pinref part="IC2" gate="D" pin="OUT"/>
<pinref part="P18" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<wire x1="195.58" y1="38.1" x2="170.18" y2="38.1" width="0.1524" layer="91"/>
<wire x1="170.18" y1="38.1" x2="170.18" y2="142.24" width="0.1524" layer="91"/>
<pinref part="IC2" gate="D" pin="IN-"/>
<pinref part="P8" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="R11" gate="G$1" pin="1"/>
<wire x1="116.84" y1="43.18" x2="134.62" y2="43.18" width="0.1524" layer="91"/>
<wire x1="134.62" y1="43.18" x2="182.88" y2="43.18" width="0.1524" layer="91"/>
<pinref part="C4" gate="G$1" pin="1"/>
<wire x1="134.62" y1="40.64" x2="134.62" y2="43.18" width="0.1524" layer="91"/>
<junction x="134.62" y="43.18"/>
<pinref part="IC1" gate="G$1" pin="D"/>
<wire x1="101.6" y1="78.74" x2="116.84" y2="78.74" width="0.1524" layer="91"/>
<wire x1="116.84" y1="78.74" x2="116.84" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
