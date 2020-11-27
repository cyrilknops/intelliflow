# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\11800025\Documents\GitHub\intelliflow\2020-2021\PCB\TestCodesPCB\PSoc_Slave_Codes\SPI_Slave_FullDuplex.cydsn\SPI_Slave_FullDuplex.cyprj
# Date: Fri, 27 Nov 2020 00:16:31 GMT
#set_units -time ns
create_clock -name {UART_Putty_SCBCLK(FFB)} -period 8687.5 -waveform {0 4343.75} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 17 33} [list [get_pins {ClockBlock/udb_div_0}]]
create_generated_clock -name {UART_Putty_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 417 835} [list]


# Component constraints for C:\Users\11800025\Documents\GitHub\intelliflow\2020-2021\PCB\TestCodesPCB\PSoc_Slave_Codes\SPI_Slave_FullDuplex.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\11800025\Documents\GitHub\intelliflow\2020-2021\PCB\TestCodesPCB\PSoc_Slave_Codes\SPI_Slave_FullDuplex.cydsn\SPI_Slave_FullDuplex.cyprj
# Date: Fri, 27 Nov 2020 00:16:26 GMT
