/*
 * uugp_can.c
 *
 *  Created on: Apr 20, 2022
 *      Author: BiancaNobelia
 *      teuku zikri fatahillah
 */

#include "uugp_can.h"

CAN_RxHeaderTypeDef rx_header; //CAN Bus Transmit Header
CAN_TxHeaderTypeDef tx_header; //CAN Bus Receive Header
uint32_t mail_box;
uint32_t voltage;

UUGP_Typedef UUGP_Data;

/*Set the output reference voltage of module 1 (the address of module 1 is 0x01) */
void SetOutputReferenceVoltage(CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t reference_voltage)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	uint8_t GroupAddress = 0x01;
	uint8_t MessageType = SetData;
	uint8_t CommandType = VoutReference;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = reference_voltage;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void SetCurrentLimit(CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t current_limit)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = SetData;
	uint8_t CommandType = IoutLimit;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = current_limit;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void ReadOutputVoltage (CAN_HandleTypeDef *hcan, uint8_t module_address)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = ReadData;
	uint8_t CommandType = Vout;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = 0x00;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void ReadOutputCurrent (CAN_HandleTypeDef *hcan, uint8_t module_address)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = ReadData;
	uint8_t CommandType = Iout_slow;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = 0x00;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void PowerOnModule (CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t power_on)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = SetData;
	uint8_t CommandType = ShutDownDCDC;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = power_on;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void ShutdownModule (CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t shutdown)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = SetData;
	uint8_t CommandType = ShutDownDCDC;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = shutdown;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void ReadStatusFlag (CAN_HandleTypeDef *hcan, uint8_t module_address)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = ReadData;
	uint8_t CommandType = ModuleStatus;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = 0x00;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void SetVoltageMode (CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t set_voltage)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = SetData;
	uint8_t CommandType = HiMode_LoMode_Selection;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = set_voltage;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void ReadVoltageMode (CAN_HandleTypeDef *hcan, uint8_t module_address)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = ReadData;
	uint8_t CommandType = HiMode_LoMode_Status;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = 0x00;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void SetGroupAddress (CAN_HandleTypeDef *hcan, uint8_t module_address, uint32_t set_address)
{
	uint8_t Protocol = 0x01;
	uint8_t MonitorAddress = 0x01;
	uint8_t ModuleAddress = module_address;
	uint8_t ProductionDate = 0x00;
	uint16_t SerialNumberLowerPart = 0x00;

	uint32_t IdentifierField = 0;

	IdentifierField |= (SerialNumberLowerPart << StartBit_serialNumberLowerPart);
	IdentifierField |= (ProductionDate << StartBit_ProductionDate);
	IdentifierField |= (ModuleAddress << StartBit_ModuleAddress);
	IdentifierField |= (MonitorAddress << StartBit_MonitorAddress);
	IdentifierField |= (Protocol << StartBit_Protocol);

	tx_header.IDE = CAN_ID_EXT;
	tx_header.StdId = 0x00;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.ExtId = IdentifierField;
	tx_header.TransmitGlobalTime = DISABLE;

	int8_t GroupAddress = 0x01;
	uint8_t MessageType = SetData;
	uint8_t CommandType = Group_Address;
	uint8_t Reserved = 0x00;
	uint32_t CommandData = set_address;

	uint8_t DataField[8];

	DataField[0] = MessageType;
	DataField[0] |= GroupAddress << 4;
	DataField[1] = CommandType;
	DataField[2] = Reserved;
	DataField[3] = Reserved;

	DataField[4] = CommandData >> 24;
	DataField[5] = CommandData >> 16;
	DataField[6] = CommandData >> 8;
	DataField[7] = CommandData;

	HAL_CAN_AddTxMessage(hcan, &tx_header, DataField, &mail_box);

}

void ReadFeedback(CAN_HandleTypeDef *hcan)
{
	uint8_t rx_data[8];
	uint8_t Protocol;
	uint8_t MonitorAddress;
	uint8_t ModuleAddress;
	uint8_t ProductionDate;
	uint16_t SerialNumberLowerPart;
	uint32_t IdentifierField;

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
	IdentifierField = rx_header.ExtId;

	SerialNumberLowerPart = IdentifierField >> StartBit_serialNumberLowerPart ;
	ProductionDate = IdentifierField >> StartBit_ProductionDate;
	ModuleAddress = IdentifierField >> StartBit_ModuleAddress;
	MonitorAddress = IdentifierField >> StartBit_MonitorAddress;
	Protocol = IdentifierField >> StartBit_Protocol;

	int8_t GroupAddress;
	uint8_t MessageType;
	uint8_t CommandType;
	uint8_t Reserved;
	uint32_t CommandData;

	MessageType = rx_data[0] & 0x0F;
	GroupAddress = rx_data[0] >> 4;
	CommandType = rx_data[1];
	Reserved = rx_data[2];
	Reserved = rx_data[3];
	CommandData = ((uint32_t)rx_data[4]) | ((uint32_t)rx_data[5] << 8) | ((uint32_t)rx_data[6] << 16) | ((uint32_t)rx_data[7] << 24);

	if (MessageType = ReadDataResponse)
	{
		switch (CommandType)
			{
				case Vout: //0
					UUGP_Data.Output_Voltage = CommandData;
					break;
				case Iout_slow: //1
					UUGP_Data.Output_Current = CommandData;
					break;
				case VoutReference: //2
					UUGP_Data.Output_Reference = CommandData;
					break;
				case IoutLimit: //3
					UUGP_Data.Current_Limit = CommandData;
					break;
				case ShutDownDCDC: //4
					UUGP_Data.Power_Modul = CommandData;
					break;
				case ModuleStatus: //8
					UUGP_Data.Status_Flag = CommandData;
					break;
				case Vab: //20
					UUGP_Data.Voltage_AB = CommandData;
					break;
				case Vbc: //21
					UUGP_Data.Voltage_BC = CommandData;
					break;
				case Vac: //22
					UUGP_Data.Voltage_CA = CommandData;
					break;
				case Tin: //30
					UUGP_Data.Inlet_Temperature = CommandData;
					break;
				case Iout_fastest: //47
					UUGP_Data.Current_Fastest = CommandData;
					break;
				case Iout_fast: //48
					UUGP_Data.Current_Fast = CommandData;
					break;
				case Group_Address: //89
					UUGP_Data.Address_Group = CommandData;
					break;
				case HiMode_LoMode_Selection: //95
					UUGP_Data.Mode_Selection = CommandData;
					break;
				case HiMode_LoMode_Status: //96
					UUGP_Data.Mode_Status = CommandData;
					break;
				case Vout_fast: //98
					UUGP_Data.Voltage_Fast = CommandData;
					break;
				case CurrentCapability:
					UUGP_Data.Current_Capability = CommandData;
					break;
			}
	}

}

