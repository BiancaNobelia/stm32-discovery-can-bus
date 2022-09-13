/*
 * uugp_can.h
 *
 *  Created on: Apr 20, 2022
 *      Author: BiancaNobelia
 *      teuku zikri fatahillah
 */

#ifndef INC_UUGP_CAN_H_
#define INC_UUGP_CAN_H_

#include "main.h"
#include "stm32f4xx_hal_can.h"

#define IDENTIFIER_FIELD 29 //bits
#define DATA_FIELD 8 //bytes

#define StartBit_serialNumberLowerPart 0
#define StartBit_ProductionDate 9
#define StartBit_ModuleAddress 14 //between 0x01-0x7F and 0x00 for broadcast
#define StartBit_MonitorAddress 21
#define StartBit_Protocol 25

#define BROADCAST_ADDR 0x00

enum message_type
{
	SetData = 0,
	SetDataResponse = 1,
	ReadData = 2,
	ReadDataResponse = 3
};

enum command_type
{
	Vout = 0,//Module output voltage
	Iout_slow = 1,//Module output current
	VoutReference = 2,//Module output reference voltage
	IoutLimit = 3, //Module output current limit
	ShutDownDCDC = 4, //Turn on/off power module
	ModuleStatus = 8, //Module status flag
	Vab = 20, //Line voltage AB
	Vbc = 21, //Line voltage BC
	Vac = 22, //Line voltage CA
	Tin = 30, //Inlet Temperature
	Iout_fastest = 47, //Module output current (fastest)
	Iout_fast = 48, //Module output current (fast)
	Group_Address = 89, //Group address
	HiMode_LoMode_Selection = 95, //HiMode_LoMode_Selection
	HiMode_LoMode_Status = 96, //HiMode_LoMode_Status
	Vout_fast = 98, //Module output voltage (fast)
	CurrentCapability = 104 //Module Output Current Capability
};

enum voltage_mode
{
	 HiMode = 1, //1000v
	 LoMode = 2 //500v
};

enum error_flag
{
	AC_over_voltage = 0x01,
	AC_under_voltage = 0x02,
	Disconnect_from_AC = 0x04,
	DC_output_over_voltage = 0x40,
	DC_over_voltage_shutdown = 0x80,
	DC_output_undervoltage = 0x100,
	Fan_stops_operating = 0x200,
	Over_temperature = 0x1000,
	PFC_over_temperature_protection1 = 0x4000,
	PFC_over_temperature_protection2 = 0x8000,
	DC_over_temperature_protection1 = 0x10000,
	DC_over_temperature_protection2 = 0x20000,
	Communication_failure_between_PFC_and_DCDC = 0x40000,
	PFC_failure = 0x100000,
	DCDC_failure = 0x200000,
	Module_turn_on_off = 0x2000000,
	BleederNotWork = 0x80000000,
};

extern CAN_RxHeaderTypeDef rx_header; //CAN Bus Transmit Header
extern CAN_TxHeaderTypeDef tx_header; //CAN Bus Receive Header
extern uint32_t mail_box;

typedef struct UUGPListData
{
	uint32_t Output_Voltage;
	uint32_t Output_Current;
	uint32_t Output_Reference;
	uint32_t Current_Limit;
	uint32_t Power_Modul;
	uint32_t Status_Flag;
	uint32_t Voltage_AB;
	uint32_t Voltage_BC;
	uint32_t Voltage_CA;
	uint32_t Inlet_Temperature;
	uint32_t Current_Fastest;
	uint32_t Current_Fast;
	uint32_t Address_Group;
	uint32_t Mode_Selection;
	uint32_t Mode_Status;
	uint32_t Voltage_Fast;
	uint32_t Current_Capability;
} UUGP_Typedef;

extern UUGP_Typedef UUGP_Data;

void SetOutputReferenceVoltage(CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t reference_voltage);
void SetCurrentLimit(CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t current_limit);
void ReadOutputVoltage (CAN_HandleTypeDef *hcan, uint8_t module_address);
void ReadOutputCurrent (CAN_HandleTypeDef *hcan, uint8_t module_address);
void PowerOnModule (CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t power_on);
void ShutdownModule (CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t shutdown);
void ReadStatusFlag (CAN_HandleTypeDef *hcan, uint8_t module_address);
void SetVoltageMode (CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t set_voltage);
void ReadVoltageMode (CAN_HandleTypeDef *hcan, uint8_t module_address);
void SetGroupAddress (CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t set_address);
void ReadFeedback(CAN_HandleTypeDef *hcan);

#endif /* INC_UUGP_CAN_H_ */
