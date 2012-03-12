ENTRY(MW2440Entry)

SECTIONS
{
	.text 0x0:
	{
		MW2440Entry = .;
		*(.text)
	}

	.data ALIGN(4):
	{
		data_start = .;
		*(.data)
	}

	.bss ALIGN(4):
	{
		bss_start = .;
		*(.bss)
	}

	MW2440End = .;
}
