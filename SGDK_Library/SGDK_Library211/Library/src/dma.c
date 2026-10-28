#include "dma.h"

DMAOpInfo *dmaQueues = NULL;
u16* dmaDataBuffer = NULL;

void DMA_init(void) {}

void DMA_initEx(u16 size, u16 capacity, u16 bufferSize) {}

bool DMA_getAutoFlush(void) { return 0; }

void DMA_setAutoFlush(bool value) {}

u16 DMA_getMaxQueueSize(void) { return 0; }

void DMA_setMaxQueueSize(u16 value) {}

void DMA_setMaxQueueSizeToDefault(void) {}

u16 DMA_getMaxTransferSize(void) { return 0; }

void DMA_setMaxTransferSize(u16 value) {}

void DMA_setMaxTransferSizeToDefault(void) {}

u16 DMA_getBufferSize(void) { return 0; }

void DMA_setBufferSize(u16 value) {}

void DMA_setBufferSizeToDefault(void) {}

bool DMA_getIgnoreOverCapacity(void) { return 0; }

void DMA_setIgnoreOverCapacity(bool value) {}

void DMA_clearQueue(void) {}

void DMA_flushQueue(void) {}

u16 DMA_getQueueSize(void) { return 0; }

u16 DMA_getQueueTransferSize(void) { return 0; }

void*DMA_allocateTemp(u16 len) { return 0; }

void DMA_releaseTemp(u16 len) {}

bool DMA_transfer(TransferMethod tm, u8 location, void* from, u16 to, u16 len, u16 step) { return 0; }

bool DMA_canQueue(u8 location, u16 len) { return 0; }

void*DMA_allocateAndQueueDma(u8 location, u16 to, u16 len, u16 step) { return 0; }

bool DMA_copyAndQueueDma(u8 location, void* from, u16 to, u16 len, u16 step) { return 0; }

bool DMA_queueDma(u8 location, void* from, u16 to, u16 len, u16 step) { return 0; }

bool DMA_queueDmaFast(u8 location, void* from, u16 to, u16 len, u16 step) { return 0; }

void DMA_doDma(u8 location, void* from, u16 to, u16 len, s16 step) {}

void DMA_doDmaFast(u8 location, void* from, u16 to, u16 len, s16 step) {}

void DMA_doCPUCopy(u8 location, void* from, u16 to, u16 len, s16 step) {}

void DMA_doCPUCopyDirect(u32 cmd, void* from, u16 len, s16 step) {}

void DMA_doVRamFill(u16 to, u16 len, u8 value, s16 step) {}

void DMA_doVRamCopy(u16 from, u16 to, u16 len, s16 step) {}

void DMA_waitCompletion(void) {}

