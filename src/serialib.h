/**
 \class     serialib
 \brief     Classe utilisé pour la voie série
 
 */
#ifndef SERIALIB_H
#define SERIALIB_H


// Used for TimeOut operations
#include <sys/timeb.h>
// Include for windows
#if defined (_WIN32) || defined( _WIN64)
    // Accessing to the serial port under Windows
    #include <windows.h>
#endif

// Include for Linux
#ifdef __linux__
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/shm.h>
    #include <termios.h>
    #include <string.h>
    #include <iostream>
    // File control definitions
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif



class serialib
{
public:
    // Constructor of the class
    serialib    ();

    // Destructor
    ~serialib   ();



    //_________________________________________
    // ::: Configuration and initialization :::


    // Open a device
    char    Open        (const char *Device,const unsigned int Bauds);

    // Close the current device
    void    Close();



    //___________________________________________
    // ::: Read/Write operation on characters :::


    // Write a char
    char    WriteChar   (char);

    // Read a char (with timeout)
    char    ReadChar    (char *pByte,const unsigned int TimeOut_ms=NULL);



    //________________________________________
    // ::: Read/Write operation on strings :::


    // Write a string
    char    WriteString (const char *String);
    // Read a string (with timeout)
    int     ReadString  (   char *String,
                            char FinalChar,
                            unsigned int MaxNbBytes,
                            const unsigned int TimeOut_ms=NULL);



    // _____________________________________
    // ::: Read/Write operation on bytes :::


    // Write an array of bytes
    char    Write       (const void *Buffer, const unsigned int NbBytes);

    // Read an array of byte (with timeout)
    int     Read        (void *Buffer,unsigned int MaxNbBytes,const unsigned int TimeOut_ms=NULL);


    // _________________________
    // ::: Special operation :::


    // Empty the received buffer
    void    FlushReceiver();

    // Return the number of bytes in the received buffer
    int     Peek();

private:
    // Read a string (no timeout)
    int     ReadStringNoTimeOut  (char *String,char FinalChar,unsigned int MaxNbBytes);


#if defined (_WIN32) || defined( _WIN64)
    HANDLE          hSerial;
    COMMTIMEOUTS    timeouts;
#endif
#ifdef __linux__
    int             fd;
#endif

};

  //Classe de gestion de temps utiliser dans la classes serialib
   
/**
 \class     TimeOut
 \brief     Classe de gestion de temps utiliser dans la classes serialib
 
 */
// Class TimeOut
class TimeOut
{
public:

    // Constructor
    TimeOut();

    // Init the timer
    void                InitTimer();

    // Return the elapsed time since initialization
    unsigned long int   ElapsedTime_ms();

private:    
    struct timeval      PreviousTime;
};



/*
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This is a licence-free software, it can be used by anyone who try to build a better world.
*/


#endif // SERIALIB_H

