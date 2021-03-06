# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Luggi\Documents\GitHub\laserschutzschaltung\Laserschutzschaltung.cydsn\Laserschutzschaltung.cyprj
# Date: Mon, 29 May 2017 12:29:24 GMT
#set_units -time ns
create_clock -name {CyBUS_CLK(routed)} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/clk_bus}]]
create_clock -name {ADC_DelSig_1_Ext_CP_Clk(routed)} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/dclk_2}]]
create_clock -name {ADC_SAR_Seq_2_IntClock(routed)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/dclk_3}]]
create_clock -name {ADC_SAR_1_theACLK(routed)} -period 833.33333333333326 -waveform {0 416.666666666667} [list [get_pins {ClockBlock/dclk_4}]]
create_clock -name {CyXTAL_32kHz} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/clk_32k_xtal}]]
create_clock -name {CyXTAL} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/xtal}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {Clock_5} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} -nominal_period 41.666666666666664 [list [get_pins {ClockBlock/dclk_glb_0}]]
create_clock -name {Clock_5(fixed-function)} -period 31.25 -waveform {0 15.625} -nominal_period 41.666666666666664 [get_pins {ClockBlock/dclk_glb_ff_0}]
create_clock -name {ADC_DelSig_1_Ext_CP_Clk} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {ADC_SAR_Seq_2_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 41 81} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {ADC_DelSig_1_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 157 313} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_clock -name {ADC_DelSig_1_theACLK(fixed-function)} -period 2437.5 -waveform {0 1218.75} [get_pins {ClockBlock/aclk_glb_ff_0}]
create_generated_clock -name {Clock_4} -source [get_pins {ClockBlock/clk_sync}] -edges {1 6398439 12800781} -nominal_period 100006103.515625 [list [get_pins {ClockBlock/dclk_glb_5}]]
create_clock -name {Clock_4(fixed-function)} -period 100006093.75 -waveform {0 15.625} -nominal_period 100006103.515625 [get_pins {ClockBlock/dclk_glb_ff_5}]
create_generated_clock -name {Clock_3} -source [get_pins {ClockBlock/clk_sync}] -edges {1 1335 2667} -nominal_period 20833.333333333332 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_clock -name {Clock_3(fixed-function)} -period 20828.125 -waveform {0 15.625} -nominal_period 20833.333333333332 [get_pins {ClockBlock/dclk_glb_ff_1}]
create_generated_clock -name {ADC_SAR_1_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 55 107} -nominal_period 833.33333333333326 [list [get_pins {ClockBlock/dclk_glb_4}]]

set_false_path -from [get_pins {__ONE__/q}]
set_false_path -from [get_pins {__ZERO__/q}]

# Component constraints for C:\Users\Luggi\Documents\GitHub\laserschutzschaltung\Laserschutzschaltung.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Luggi\Documents\GitHub\laserschutzschaltung\Laserschutzschaltung.cydsn\Laserschutzschaltung.cyprj
# Date: Mon, 29 May 2017 12:29:09 GMT
