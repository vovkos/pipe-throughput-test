#pragma once

//..............................................................................

// pipe config

#define MY_PIPE_NAMEA           "\\\\.\\pipe\\pipe-throughput-test"
#define MY_PIPE_NAMEW           _CRT_WIDE (MY_PIPE_NAMEA)

#define MY_PIPE_MESSAGE_MODE    0

#if (MY_PIPE_MESSAGE_MODE)
#	define MY_PIPE_MODE         (PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE)
#else
#	define MY_PIPE_MODE         (PIPE_TYPE_BYTE | PIPE_READMODE_BYTE)
#endif

#define MY_PIPE_RX_BUFFER_SIZE  (4 * 1024)
#define MY_PIPE_TX_BUFFER_SIZE  (4 * 1024)
#define MY_PIPE_TIMEOUT         0

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// tra

#define MY_TRANSFER_TOTAL_SIZE (8 * 1024 * 1024) // 8MB
#define MY_TRANSFER_BLOCK_SIZE (1 * 1024)        // 1KB

//..............................................................................
