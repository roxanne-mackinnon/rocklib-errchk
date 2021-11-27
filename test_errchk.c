#include <stdio.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "errchk.h"



unsigned test_messages(unsigned times, float error_rate);

void check_args(int argc, char * argv[]);


char rand_4bit_mess(void);

char apply_noise(char message, float error_rate);

int test_one_message(float error_rate);

int one_with_probability(float p);

int main
(int argc, char * argv[])
{
  // check program arguments and set random seed
  check_args(argc, argv);
  srand(time(NULL));

  // extract iterations and probability
  unsigned times = atoi(argv[1]);
  float error_rate = atof(argv[2]);

  // test 'times' messages with the given error rate (possibly 0)
  unsigned num = test_messages(times, error_rate);

  printf("Number of tests passed: %u / %u\n", num, times);
  
  return 0;
}

/**
 * Test decoding algorithm against 'times' noisy 4-bit messages (encoded to 7-bits).
 * Issues a warning to stderr if any failed cases occur.
 * Returns: The number of test cases passed
 */
unsigned test_messages(unsigned times, float error_rate) {
  unsigned num_passed = 0;
  
  while (times--) {
    // if test passes, increment number of passed tests.
    if (test_one_message(error_rate)) {
      num_passed++;
    }
  }
  return num_passed;
}

/**
 * Test a single message, generated randomly, against the given error rate.
 */
int test_one_message(float error_rate) {
  char message = rand_4bit_mess();
  char encoding = errchk_encode(message);
  char noisy_mess = apply_noise(encoding, error_rate);
  char decoding = errchk_decode(noisy_mess);
  return (message == decoding);
}


/**
 * Generate a random 4 bit message as a char.
 * The upper bits of the 8 bit char will be 0.
 */
char rand_4bit_mess (void)
{
  // 15 == 0x0f == 0000 1111
  return rand() & 15;
}

/**
 * Return 1 with the given probability, 0 otherwise.  
 */
int one_with_probability(float error_rate) {
  return ((float) rand() / RAND_MAX) < error_rate;
}


/**
 * Apply noise to the given 7 bit message, with the given uniform error rate.
 * Returns: the original 7 bit message with possibly multiple flipped bits.
 */
char apply_noise(char message, float error_rate) {

  // for each bit in the 7 bit message
  for (char bit = 0; bit < 6; bit++) {
    // flip that bit with the given probability of error_rate
    if (one_with_probability(error_rate)) {
      message ^= (1<<bit);
    }
  }
  return message;
}


/**
 * Verify that valid arguments were passed to the program.
 * Exit after printing a usage string if the arguments are not valid.
 */
void check_args(int argc, char * argv[]) {

  // ensure correct number of arguments
  if (argc != 3) {
    fprintf(stderr, "usage: %s <iterations> <error_rate>\n", argv[0]);
    exit(1);
  }

  // ensure error_rate argument represents a probability
  float error_rate = atof(argv[2]);
  if (error_rate < 0.0 || error_rate > 1.0) {
    fprintf(stderr, "error: <error_rate> must be a floating point"
	    " value between 0.0 and 1.0 inclusive.\n");
    exit(1);
  }

}
