#define ANGLE_RESET 32768           // Halfway through the count range of [0, 2^16)
#define ENCODER_LINES 448
#define RESOLUTION 4
#define CYCLE_COUNTS (ENCODER_LINES * RESOLUTION)       // Each line has a resolution of 4, then consider 360 degrees


// Prototypes
int encoder_counts(void);
void encoder_init(void);
void encoder_reset(void);
int encoder_angle(void);
