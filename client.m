function client(port)
%   provides a menu for accessing PIC32 motor control functions
%
%   client(port)
%
%   Input Arguments:
%       port - the name of the com port.  This should be the same as what
%               you use in screen or putty in quotes ' '
%
%   Example:
%       client('/dev/ttyUSB0') (Linux/Mac)
%       client('COM3') (PC)
%
%   For convenience, you may want to change this so that the port is hardcoded.
   
% Opening COM connection
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end

% My port : '/dev/tty.usbserial-DM01N1JX'
fprintf('Opening port %s....\n',port);

% settings for opening the serial port. baud rate 230400, hardware flow control
% wait up to 120 seconds for data before timing out
mySerial = serial(port, 'BaudRate', 230400, 'FlowControl', 'hardware','Timeout',120); 
% opens serial connection
fopen(mySerial);
% closes serial port when function exits
clean = onCleanup(@()fclose(mySerial));                                 

has_quit = false;
% menu loop
while ~has_quit
    fprintf('PIC32 MOTOR DRIVER INTERFACE\n\n');
    % display the menu options; this list will grow
    fprintf('\ta: Read current sensor (ADC counts)\tb: Read current sensor(mA)\n');
    fprintf('\tc: Read encoder(counts)\t\t\td: Read encoder {deg : [-180,180]}\n ');
    fprintf('\te: Reset encoder\t\t\tf: Set PWM(-100 to 100)\n');
    fprintf('\tq: Quit\n');

    % read the user's choice
    selection = input('\nENTER COMMAND: ', 's');
      
    % send the command to the PIC32
    fprintf(mySerial,'%c\n',selection);
    
    % take the appropriate action
    switch selection
        case 'c'
            counts = fscanf(mySerial,'%d');         % Get the encoder count
            fprintf('Read: %d\n', counts);          % print it to the screen            
        case 'd'                         
            angle = fscanf(mySerial,'%d');          % get the motor angle (deg)
            fprintf('Read: %d\n', angle);           % print it to the screen
        case 'e'
            fprintf('Encoder angle has been reset.\n');
        case 'q'
            has_quit = true;             % exit client
        otherwise
            fprintf('Invalid Selection %c\n', selection);
    end
end

end
