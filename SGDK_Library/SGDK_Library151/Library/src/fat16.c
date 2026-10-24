#include "fat16.h"

Fat16PBR fat16_pbr = { NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL };


u8 fat16Init()
{
	return 0;
}
u8 fat16OpenDir( u16 entry, Fat16Dir *dir )
{
	return 0;
}
u8 fat16OpenFile( Fat16Record *rec, Fat16File *file )
{
	return 0;
}
u8 fat16ReadNextSector( Fat16File *file )
{
	return 0;
}
u8 fat16WriteNextSector( Fat16File *file )
{
	return 0;
}
u8 fat16DeleteRecord( Fat16Record *rec )
{
	return 0;
}
u8 fat16CreateRecord( Fat16Record *rec, Fat16Dir *dir )
{
	return 0;
}
u8 fat16SkipSectors( Fat16File *file, u16 num )
{
	return 0;
}