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
		"Named pipe throughput test (client side)\n"
		"Press Ctrl+C to interrupt at any time\n"
		"Connecting to a named pipe server on %s...\n", 
		MY_PIPE_NAMEA
		);

	io::win::File pipe;
	result = pipe.create (
		MY_PIPE_NAMEW, 
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0
		);

	if (!result)
	{
		printf ("Error: %s...\n", err::getLastErrorDescription ().sz ());
		return -1;
	}

	printf ("Receiving %d bytes in %d blocks...\n", MY_TRANSFER_TOTAL_SIZE, MY_TRANSFER_BLOCK_SIZE);

	size_t size = 0;
	
	sl::Array <char> block;
	block.setCount (MY_TRANSFER_BLOCK_SIZE);

	printf ("0%%");

	uint64_t baseTimestamp = sys::getTimestamp ();

	for (;;)
	{
		char cmdBuffer [40] = "get-block";
		pipe.write (cmdBuffer, sizeof (cmdBuffer)); // send a "command"

		size_t actualSize = pipe.read (block, MY_TRANSFER_BLOCK_SIZE);
		if (actualSize == -1)
		{
			printf ("Error: %s...\n", err::getLastErrorDescription ().sz ());
			return -1;
		}

		size += actualSize;
		if (size >= MY_TRANSFER_TOTAL_SIZE)
			break;

		printf ("\b\b\b\b\b%lld%%", (uint64_t) size * 100 / MY_TRANSFER_TOTAL_SIZE);
	}

	uint64_t time = sys::getTimestamp () - baseTimestamp;

	printf ("\b\b\b\b\bTime: %s\n", sys::Time (time, 0).format ("%m:%s.%l").sz ());

	return 0;
}

//..............................................................................
