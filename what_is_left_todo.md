$((1 + +1)) SEG FAULT


# Des leaks!
==14600== 27 bytes in 1 blocks are definitely lost in loss record 20 of 83
==14600==    at 0x4841794: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==14600==    by 0x11E53F: ft_strjoin (in /home/thib/code/minishell/minishell)
==14600==    by 0x10C728: get_histfile (history_utils.c:29)
==14600==    by 0x10C1EB: write_hist (history.c:22)
==14600==    by 0x114EEF: check_hist (execution_doer.c:101)
==14600==    by 0x11455B: execute_the_line (execution.c:32)
==14600==    by 0x10AB70: exec_loop (shellpticflesh_more.c:38)
==14600==    by 0x10AD6C: cmd_processing (cmd_processing.c:40)
==14600==    by 0x10AA2D: main (shellpticflesh.c:117)
