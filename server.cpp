#include "pch.h"
#include "config.h"

//..............................................................................

int
main (
	int argc,
	char* argv []
	)
{
	bool result;

	printf (
		"Named pipe throughput test (server side)\n"
		"Press Ctrl+C to interrupt at any time\n"
		"Starting a named pipe server on %s...\n", 
		MY_PIPE_NAMEA
		);

	io::win::NamedPipe pipe;
	result = pipe.create (
		MY_PIPE_NAMEW, 
		PIPE_ACCESS_DUPLEX, 
		MY_PIPE_MODE,
		PIPE_UNLIMITED_INSTANCES,
		MY_PIPE_TX_BUFFER_SIZE,
		MY_PIPE_RX_BUFFER_SIZE,
		MY_PIPE_TIMEOUT,
		NULL
		);

	if (!result)
	{
		printf ("Error: %s...\n", err::getLastErrorDescription ().sz ());
		return -1;
	}

	printf ("Accepting pipe connection...\n");

	result = pipe.connect ();
	if (!result)
	{
		printf ("Error: %s...\n", err::getLastErrorDescription ().sz ());
		return -1;
	}

	printf ("Sending %d bytes in %d blocks...\n", MY_TRANSFER_TOTAL_SIZE, MY_TRANSFER_BLOCK_SIZE);

	size_t size = 0;
	
	sl::Array <char> block;
	block.setCount (MY_TRANSFER_BLOCK_SIZE);

	printf ("0%%");

	uint64_t baseTimestamp = sys::getTimestamp ();

	for (;;)
	{
		char cmdBuffer [1024];
		pipe.read (cmdBuffer, sizeof (cmdBuffer)); // wait for a "command"

		for (size_t i = 0; i < MY_TRANSFER_BLOCK_SIZE; i++)
			block [i] = i + size;

		size_t actualSize = pipe.write (block, MY_TRANSFER_BLOCK_SIZE);
		if (actualSize == -1)
		{
			printf ("Error: %s...\n", err::getLastErrorDescription ().sz ());
			return -1;
		}

		size += actualSize;
		if (size >= MY_TRANSFER_TOTAL_SIZE)
			break;

		printf ("\b\b\b\b\b%llu%%", (uint64_t) size * 100 / MY_TRANSFER_TOTAL_SIZE);
	}

	uint64_t time = sys::getTimestamp () - baseTimestamp;

	printf ("\b\b\b\b\bTime: %s\n", sys::Time (time, 0).format ("%m:%s.%l").sz ());

	return 0;
}

//..............................................................................
