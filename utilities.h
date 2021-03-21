/* Enum for the 5 different operating modes */
typedef enum{
    IDLE,
    PWM,
    ITEST,
    HOLD,
    TRACK
}mode;

/* Holder for the current mode */
static mode MODE;

/* Prototypes */
void set_mode(mode new_m);
mode get_mode(void);
