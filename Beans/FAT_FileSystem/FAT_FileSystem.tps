<?xml version="1.0" encoding="UTF-8"?>
<TypesAndGlobals>
  <Types>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeMaxSS</Name>
      <Items lines_count="4">
        <Line>512</Line>
        <Line>1024</Line>
        <Line>2048</Line>
        <Line>4096</Line>
      </Items>
      <Hints lines_count="4">
        <Line>Sector size of 512 bytes, usually for memory card and floppy disk</Line>
        <Line>Sector size of 1024 bytes, usually for floppy disk</Line>
        <Line>Sector size of 2048 bytes, usually for MO disk</Line>
        <Line>Sector size of 4096 bytes.</Line>
      </Hints>
      <Defines lines_count="4">
        <Line>512</Line>
        <Line>1024</Line>
        <Line>2048</Line>
        <Line>4096</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeRelPath</Name>
      <Items lines_count="3">
        <Line>Disabled</Line>
        <Line>Enabled</Line>
        <Line>Enabled with f_getcwd()</Line>
      </Items>
      <Hints lines_count="3">
        <Line>Disable relative path feature and remove related functions.</Line>
        <Line>Enable relative path. f_chdrive() and f_chdir() are available.</Line>
        <Line>f_getcwd() is available in addition to 'Enabled'</Line>
      </Hints>
      <Defines lines_count="3">
        <Line>0</Line>
        <Line>1</Line>
        <Line>2</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeCodePage</Name>
      <Items lines_count="26">
        <Line>ASCII (for only non-LFN cfg)</Line>
        <Line>U.S. (OEM)</Line>
        <Line>Arabic</Line>
        <Line>Greek (OEM)</Line>
        <Line>Baltic (OEM)</Line>
        <Line>Multilingual Latin 1 (OEM)</Line>
        <Line>Turkish (OEM)</Line>
        <Line>Latin 2 (OEM)</Line>
        <Line>Cyrillic (OEM)</Line>
        <Line>Multilingual Latin 1 + Euro (OEM)</Line>
        <Line>Hebrew (OEM)</Line>
        <Line>Russian (OEM)</Line>
        <Line>Thai (OEM, Windows)</Line>
        <Line>Japanese Shift-JIS</Line>
        <Line>Simplified Chinese GBK</Line>
        <Line>Korean</Line>
        <Line>Traditional Chinese Big5</Line>
        <Line>Central Europe (Windows)</Line>
        <Line>Cyrillic (Windows)</Line>
        <Line>Latin 1 (Windows)</Line>
        <Line>Greek (Windows)</Line>
        <Line>Turkish (Windows)</Line>
        <Line>Hebrew (Windows)</Line>
        <Line>Arabic (Windows)</Line>
        <Line>Baltic (Windows)</Line>
        <Line>Vietnam (OEM, Windows)</Line>
      </Items>
      <Hints lines_count="26">
        <Line>ASCII (for only non-LFN cfg) (1)</Line>
        <Line>U.S. (OEM) (437)</Line>
        <Line>Arabic (OEM) (720)</Line>
        <Line>Greek (OEM) (737)</Line>
        <Line>Baltic (OEM) (775)</Line>
        <Line>Multilingual Latin 1 (OEM) (850)</Line>
        <Line>Turkish (OEM) (857)</Line>
        <Line>Latin 2 (OEM) (852)</Line>
        <Line>Cyrillic (OEM) (855)</Line>
        <Line>Multilingual Latin 1 + Euro (OEM) (858)</Line>
        <Line>Hebrew (OEM) (862)</Line>
        <Line>Russian (OEM)</Line>
        <Line>Thai (OEM, Windows) (874)</Line>
        <Line>Japanese Shift-JIS (932)</Line>
        <Line>Simplified Chinese GBK (936)</Line>
        <Line>Korean (949)</Line>
        <Line>Traditional Chinese Big5 (950)</Line>
        <Line>Central Europe (Windows) (1250)</Line>
        <Line>Cyrillic (Windows) (1251)</Line>
        <Line>Latin 1 (Windows) (1252)</Line>
        <Line>Greek (Windows) (1253)</Line>
        <Line>Turkish (Windows) (1254)</Line>
        <Line>Hebrew (Windows) (1255)</Line>
        <Line>Arabic (Windows) (1256)</Line>
        <Line>Baltic (Windows) (1257)</Line>
        <Line>Vietnam (OEM, Windows) (1258)</Line>
      </Hints>
      <Defines lines_count="26">
        <Line>1</Line>
        <Line>437</Line>
        <Line>720</Line>
        <Line>737</Line>
        <Line>775</Line>
        <Line>850</Line>
        <Line>857</Line>
        <Line>852</Line>
        <Line>855</Line>
        <Line>858</Line>
        <Line>862</Line>
        <Line>866</Line>
        <Line>874</Line>
        <Line>932</Line>
        <Line>936</Line>
        <Line>949</Line>
        <Line>950</Line>
        <Line>1250</Line>
        <Line>1251</Line>
        <Line>1252</Line>
        <Line>1253</Line>
        <Line>1254</Line>
        <Line>1255</Line>
        <Line>1256</Line>
        <Line>1257</Line>
        <Line>1258</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeLFN</Name>
      <Items lines_count="4">
        <Line>Disable</Line>
        <Line>Enable, static global buffer</Line>
        <Line>Enable, dynamic stack buffer</Line>
        <Line>Enable, dynamic heap buffer</Line>
      </Items>
      <Hints lines_count="4">
        <Line>Disable LFN feature. _MAX_LFN and _LFN_UNICODE have no effect.</Line>
        <Line>Enable LFN with static working buffer on the BSS. Always NOT reentrant.</Line>
        <Line>Enable LFN with dynamic working buffer on the STACK.</Line>
        <Line>Enable LFN with dynamic working buffer on the HEAP.</Line>
      </Hints>
      <Defines lines_count="4">
        <Line>0</Line>
        <Line>1</Line>
        <Line>2</Line>
        <Line>3</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeUseStrFunc</Name>
      <Items lines_count="3">
        <Line>disable</Line>
        <Line>enable</Line>
        <Line>enable with CR-&gt;LF conversion</Line>
      </Items>
      <Hints lines_count="3">
        <Line>disables f_putc(), f_puts(), f_printf() and f_get(s).</Line>
        <Line>enables f_putc(), f_puts(), f_printf() and f_get(s).</Line>
        <Line>same as enable, but with LR-&gt;CRLF conversion</Line>
      </Hints>
      <Defines lines_count="3">
        <Line>0</Line>
        <Line>1</Line>
        <Line>2</Line>
      </Defines>
    </Type>
  </Types>
</TypesAndGlobals>
