c88.opus     ��    Bq AW A��   
                 X4    <18>May 11 21:55:06 sendmailmaster                       are you?: N< MAILER-DAEMON @ dc   	                                ���p     Br    q   A     A� A� AWH p�   + p����   ������     BE@ A� A� A� A�   q B��    8.op����   ��� A� A�d�   ������          A A}p                    ���p     Br     ���( BQ� A
� ��   t �    q V�   
     AWh��� A}p Al Br   r  AWh A
�           
8.op B�   :   ���(���               AWh A}p AWh A}p        BQ� AWh A}p���( �� A}� ��AEMON@ma    .dc88.opus @ Br  A}p y dc88.dc88.opus (5.60/1.00)
	id AA01653; Fri, 11 May 90 21:55:05 GMT master . dc88 . opus ITNET                   ��            AWX A:� ��    AW8���h A5� A}p   master � A� @��    BqJ @�� A�(    A5�    B��     As� @�D �      g(    V� AWX AWX AW���` A�( A}� @�� A}�        Bq@ @�� A}� Bq@ Bq@ A}�   �������` �@ As� f      � AWX  �    @�� A�  A�0               As� VX��� �� As�d     ���0���     @�4 1�     ��ts
	of Fflags.
 
	The FTLMSG bit controls the writing of the error
	message on file descriptor 2.  The message is preceded
	by the string "ERROR: ", unless the global character pointer
	"Ffile" is non-zero, in which case the message is preceded
	by the string "ERROR [<Ffile>]: ".  A newline is written
	after the user supplied message.
 
	If the FTLCLN bit is on, clean_up is called with an
	argument of 0 (see clean.c).
 
	If the FTLFUNC bit is on, the function pointed to by the global
	function pointer "Ffunc" is called with the user supplied
	error message pointer as argument.
	(This feature can be used to log error messages).
 
	The FTLACT bits determine how fatal should return.
	If the FTLJMP bit is on longjmp(Fjmp) is
	called (Fjmp is a global vector of 10 words, see
	setjmp, longjmp documentation).
 
	If the FTLEXIT bit is on the value of userexit(1) is
	passed as an argument to exit(II)
	(see userexit.c).
 
	If none of the FTLACT bits are on
	(the default value for Fflags is 0), the global word
	"Fvalue" (initialized to -1) is returned.
 
	If all fatal globals have their default values, fatal simply
	returns -1.
*/

int	Fcnt;
int	Fflags;
char	*Ffile;
int	Fvalue = -1;
int	(*Ffunc)();
#ifdef clipper
double Fjmp[11/2 + 4 + 1];
#else
#ifndef m88k
int	Fjmp[10];
#endif
#endif


fatal(msg)
char *msg;
{
	++Fcnt;
	if (Fflags & FTLMSG) {
		write(2,"ERROR",5);
		if (Ffile) {
			write(2," [",2);
			write(2,Ffile,length(Ffile));
			write(2,"]",1);
		}
		write(2,": ",2);
		write(2,msg,length(msg));
		write(2,"\n",1);
	}
	if (Fflags & FTLCLN)
		clean_up(0);
	if (Fflags & FTLFUNC)
		(*Ffunc)(msg);
	switch (Fflags & FTLACT) {
	case FTLJMP:
		longjmp(Fjmp);
	case FTLEXIT:
		exit(userexit(1));
	case FTLRET:
		return(Fvalue);
	}
}
