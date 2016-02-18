/**
 * @file      main.c
 * @author    Jeramie Vens
 * @date      2015-02-11: Created
 * @date      2015-02-15: Last updated
 * @brief     Emulate a print server system
 * @copyright MIT License (c) 2015
 */
 
/*
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*/

// lab1: print server program as it is
// lab2: make as a daemon, install different printer backends
// lab3: write a kernel module that gets installed as a backend

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <semaphore.h>
#include "queue.h"
#include "print_job.h"
#include "printer.h"
#include <argp.h>

/// program version string
const char *argp_program_version = "ISU CprE308 Print Server 0.1";
/// program bug address string
const char *argp_program_bug_address = "Jeramie Vens: <vens@iastate.edu>";
/// program documentation string
static char doc[] = "Print server -- For my class\vThis should be at the bottom";

// list of options supported
static struct argp_option options[] = 
{
	{"verbose", 'v', 0, 0, "Produce verbose output"},
	{"quite", 'q', 0, 0, "Don't produce any output"},
	{"silent", 's', 0, OPTION_ALIAS, 0},
	{"log-file", 'o', "FILE", 0, "The output log file"},
	// The student should add aditional options here
	//#warning argp_option not finished
	{"n1", '1', "NUMBER", 0, "Set number of print queue 1 printers"},
	{"n2", '2', "NUMBER", 0, "Set number of print queue 2 printers"},
	{0}
};

/// arugment structure to store the results of command line parsing
struct arguments
{
	/// are we in verbose mode?
	int verbose_mode;
	/// name of the log file
	char* log_file_name;
	// The student should add anything else they wish here
	/// number of n1 printers
	int n_one_printers;
	/// number or n2 priners
	int n_two_printers;

};

/**
 * @brief     Callback to parse a command line argument
 * @param     key
 *                 The short code key of this argument
 * @param     arg
 *                 The argument following the code
 * @param     state
 *                 The state of the arg parser state machine
 * @return    0 if succesfully handeled the key, ARGP_ERR_UNKONWN if the key was uknown
 */
error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	// the student should add the additional required arguments here
	//#warning parse_opt not finished
	struct arguments *arguments = state->input;
	switch(key)
	{
		case 'v':
			arguments->verbose_mode = 2;
			break;
		case 'q':
		case 's':
			arguments->verbose_mode = 0;
			break;
		case 'o':
			arguments->log_file_name = arg;
			break;
		case '1':
			arguments->n_one_printers = atoi(arg);
			break;
		case '2':
			arguments->n_two_printers = atoi(arg);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/// The arg parser object
static struct argp argp = {&options, parse_opt, 0, doc}; //I didn't make this, this warning is not my fault

/// mutex lock for threads writing to the log file
pthread_mutex_t file_lock;

/// Parameters to pass to the print spooler thread
struct PRINTER_SPOOLER_PARAM
{
	/// The print queue that this spooler can pull off of
	queue_t print_queue_list;
	/// The printer that this spooler can print to
	printer_t printer_driver;
	/// The log file this spooler outputs to
	FILE *log_file_file;
};

/**
 * @brief     This thread represents a print spooler which directly talks to a single printer
 * @param     param
 *                 The PRINT_SPOOL_PARAM this printer should pull its jobs from, casted to a void*
 * @return    NULL
 *
 * This function should loop forever.  The basic process is as follows:
 * 1) pop a print job from this threads queue
 * 2) if it is NULL return
 * 3) print to the log file that printing of the job is starting
 * 4) call the print method on the printer object of the param and check the return
 * 5) handel errors correctly
 * 6) destroy the print job and get the next
 */
void *printer_spooler(void* param)
{
	// The student should fill in all of this function
	//#warning printer_spooler not implememnted
	struct PRINTER_SPOOLER_PARAM *myParams = (struct PRINTER_SPOOLER_PARAM *) param;
	for(;;){
		//printf("Gunna pop some shit\n");
		print_job_t *job = (print_job_t *) queue_pop(myParams->print_queue_list, QUEUE_HEAD);
		//printf("%p", job->job_name);
		if(&job==NULL)
			return NULL;
		//printf("got a job\n");
		pthread_mutex_lock(&file_lock);
		char *log_string = print_job_tostring(job);
		//printf("%s\n", log_string);
		fprintf(myParams->log_file_file, "Starting print job:\n%s", log_string);
		fflush(myParams->log_file_file);
		pthread_mutex_unlock(&file_lock);

		int ret = printer_print(myParams->printer_driver, job);
		if(ret != 0){
			pthread_mutex_lock(&file_lock);
			fprintf(myParams->log_file_file, "Failed to print job: %s, status: %d\n", log_string, ret);
			fflush(myParams->log_file_file);
			pthread_mutex_unlock(&file_lock);
		}

		print_job_destroy(job);
	}	
}

/**
 * @brief     A print server program
 * This program shall take postscript files with some special header information from stdin
 * and print them to a printer device.  For Lab 5 the only printer device you need to support
 * is the pdf_printer provided.  Keep in mind that in future labs you will be expected to
 * support additional printers, so keep your code modular.  All printers will support the
 * API shown in printer.h.  
 *
 * The program should take a number of command line arguments.  At a minimum the following
 * should be supported:
 * - -?, --help: display help information and exit												//done
 * - -V, --version: display version information and exit										//done
 * - -v, --verbose: display debugging information to stderr										//done
 * - -q, --quiet: don't display any messages or outputs unless it is a fatal error 				//done
 * - -o, --log-file: use the given log file to print out when jobs start and finish printing	//Make the spooler print to this file, getting file is done
 * - -d, --daemon: future lab will implement this 												//Don't worry about
 * - -c, --config: future lab will implement this 												//Don't worry about
 * - -p, --printer: future lab will implement this 												//Don't worry about
 * - --n1: the number of print queue 1 printers there are (future lab will remove this)			//Done
 * - --n2: the number of print queue 2 printers there are (future lab will remove this)			//Done
 *
 * The syntax of the postscrip file is as follows.  The file will be suplied through stdin for
 * this lab.  A future lab will change this to a different location, so keep in mind modularity
 * as you go.  Each job will start with header information.  Each line of header information
 * will start with a `#` followed by a keyword and an `=` sign.  You must support at minimum
 * the following commands
 * - #name=: The name of the print job.
 * - #driver=: The driver to print the job to.  For Lab 5 this will be either "pdf1" or "pdf2".
 * - #description=: A discription of the print job which will be included in the log file
 * After all of the header information will be a line starting with a `%`.  Any line following
 * from that line to the line containing `%EOF` should be interpreted as raw postscript data.
 * It should therefore all be copied into the `print_job->file` file.
 *
 * After the `%EOF` has been found a new header may begin for the next file, or if the program
 * is finished `#exit` will be supplied.
 *
 * The flow of the program should be as follows:
 * -# parse command line arguments																		//ok
 * -# create two print queues using the `queue_create()` function										//ok
 * -# install n1 pdf_printer drivers called "pdf1-%d" and n2 pdf_printer drivers called "pdf2-%d"		//ok		
 * -# create n1+n2 spooler param objects: the first n1 with one of the print queues and all the n1		//ok
 *    drivers, and the other n2 with the other print queue and all the n2 drivers						
 * -# create n1+n2 spooler threads																		//ok
 * -# create a new print job using `print_job_create()`													//ok
 * -# parse stdin to build the print job 																//ok
 * -# all postscript data should be appended to the `print_job->file` file 								//ok
 * -# when the entire job has been read the `print_job->file` file should be closed						//ok
 * -# push the print job onto the correct print queue (if the driver was pdf1 or pdf2)					//ok
 * -# parse the next print job 																			//ok
 * -# when `#exit` is recieved make sure to release all threads and join them							//ok
 * -# free all resources and exit																		//ok
 *
 * When the program is run with valgrind it should not have ANY memory leaks.  The program
 * should also never cause a segfault for any input or reason.
 */
int main(int argc, char* argv[])
{
	// parse arguments.  Look at the man pages and section 25.3 of the GNU libc manual
	// found at https://www.gnu.org/software/libc/manual/pdf/libc.pdf for more information
	// on how to use argp to parse arguments.  An example is shown below to get you started
	struct arguments arguments;
	arguments.verbose_mode = 1;
	arguments.log_file_name = "";
	arguments.n_one_printers = 0;
	arguments.n_two_printers = 0;
	FILE *log_file;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	// The student should fill in all of this section
	//#warning main not implemented

	if(strcmp(arguments.log_file_name, "")==0){
		printf("Please provide a log file with \"-o FILE\" or \"--log-file=FILE\"\n");
		exit(1);	
	}
	if(arguments.n_one_printers==0) printf("You are creating no n1 printers, if this is wrong, run the program with the command \"1 #\" or \"--n1=#\"\n");
	if(arguments.n_two_printers==0) printf("You are creating no n2 printers, if this is wrong, run the program with the command \"2 #\" or \"--n2=#\"\n");

	if (pthread_mutex_init(&file_lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        exit(-1);
    }

	if(arguments.verbose_mode == 2) printf("Opening log file\n");
	log_file = fopen(arguments.log_file_name, "w");
	if(log_file == 0)
	{
		perror("Cannot open log file");
		exit(-1);
	}

	if(arguments.verbose_mode == 2) printf("Creating print queues\n");
	queue_t print_queue_one = queue_create();
	queue_t print_queue_two = queue_create();

	if(arguments.verbose_mode == 2) printf("Creating %d print queue one printers and %d print queue two printers\n", arguments.n_one_printers, arguments.n_two_printers);
	printer_t *printers_one = malloc(arguments.n_one_printers * sizeof(printer_t));
	printer_t *printers_two = malloc(arguments.n_two_printers * sizeof(printer_t));

	int i;
	for(i=0; i<arguments.n_one_printers; i++){
		char *name = NULL;
		asprintf(&name, "pdf1-%d", i);
		printers_one[i] = printer_install(NULL, name);
	}
	for(i=0; i<arguments.n_two_printers; i++){
		char *name = NULL;
		asprintf(&name, "pdf2-%d", i);
		printers_two[i] = printer_install(NULL, name);
	}

	if(arguments.verbose_mode == 2) printf("Creating %d printer one print spooler params and %d printer two print spooler params\n", arguments.n_one_printers, arguments.n_two_printers);
	struct PRINTER_SPOOLER_PARAM *printers_one_spooler_params = malloc(arguments.n_one_printers * sizeof(struct PRINTER_SPOOLER_PARAM));
	struct PRINTER_SPOOLER_PARAM *printers_two_spooler_params = malloc(arguments.n_two_printers * sizeof(struct PRINTER_SPOOLER_PARAM));

	for(i=0; i<arguments.n_one_printers; i++){
		printers_one_spooler_params[i].print_queue_list = print_queue_one;
		printers_one_spooler_params[i].printer_driver = printers_one[i];
		printers_one_spooler_params[i].log_file_file = log_file;
	}
	for(i=0; i<arguments.n_two_printers; i++){
		printers_two_spooler_params[i].print_queue_list = print_queue_two;
		printers_two_spooler_params[i].printer_driver = printers_two[i];
		printers_two_spooler_params[i].log_file_file = log_file;
	}

	if(arguments.verbose_mode == 2) printf("Creating %d pinter one print spoolers and %d printer two print spoolers\n", arguments.n_one_printers, arguments.n_two_printers);
	int err = 0;

	pthread_t pSpoolsOne[arguments.n_one_printers];
	pthread_t pSpoolsTwo[arguments.n_two_printers];

	for(i=0; i<arguments.n_one_printers; i++){
		err = pthread_create(&pSpoolsOne[i], NULL, printer_spooler, (void *)&printers_one_spooler_params[i]);
		if(err != 0)
		{
			perror("pthread_create encountered an error");
			exit(-1);
		}
	}
	for(i=0; i<arguments.n_two_printers; i++){
		err = pthread_create(&pSpoolsTwo[i], NULL, printer_spooler, (void *)&printers_two_spooler_params[i]);
		if(err != 0)
		{
			perror("pthread_create encountered an error");
			exit(-1);
		}
	}

	print_job_t *mah_print_job = print_job_create();

	if(arguments.verbose_mode == 2) printf("Parsing job\n");
	char *str = malloc(1024 * sizeof(char));
	char *token;
	size_t *t = malloc(sizeof(size_t));
	*t = (size_t)1024;
	getline(&str, t, stdin);
	//printf("%s\n", str);
	while(strncmp(str,"#exit",5)!=0){
		//printf("In while\n");
		//printf("%s\n", str);
		if(str[0]=='#'){
			if(strncmp(str,"#device=",8)==0){
				token = strtok(str, "=");
				token = strtok(NULL, "=");
				mah_print_job->driver_name = token;
				if(arguments.verbose_mode == 2) printf("Sending job to device: %s\n", mah_print_job->driver_name);
			}
			if(strncmp(str,"#name=",6)==0){
				token = strtok(str, "=");
				token = strtok(NULL, "=");
				mah_print_job->job_name = token;
				if(arguments.verbose_mode == 2) printf("Job name: %s\n", mah_print_job->job_name);
			}
			if(strncmp(str,"#description=",13)==0){
				token = strtok(str, "=");
				token = strtok(NULL, "=");
				mah_print_job->description = token;
				if(arguments.verbose_mode == 2) printf("Job description: %s\n", mah_print_job->description);
			}
		}
		if(str[0]=='%'){
			if(arguments.verbose_mode == 2) printf("Parsing job data\n");
			FILE *job_file;
			job_file = fopen(mah_print_job->file, "w");
			if(job_file == 0)
			{
				perror("Cannot open second file");
				exit(-1);
			}
			while(strncmp(str,"%EOF",4)!=0){
				fprintf(job_file, "%s", str);
				getline(&str, t, stdin);
			}
			fclose(job_file);
			if(strcmp(mah_print_job->driver_name, "pdf1")==0){
				if(arguments.verbose_mode == 2) printf("Pushing job to pdf1");
				queue_push(print_queue_one, (void*)mah_print_job, QUEUE_TAIL);
			}
			if(strcmp(mah_print_job->driver_name, "pdf2")==0){
				if(arguments.verbose_mode == 2) printf("Pushing job to pdf2");
				queue_push(print_queue_two, (void*)mah_print_job, QUEUE_TAIL);
			}
			mah_print_job = print_job_create();
		}
		getline(&str, t, stdin);
	}

	if(arguments.verbose_mode == 2) printf("Exiting, releasing threads\n");
	queue_release_threads(print_queue_one, arguments.n_one_printers);
	queue_release_threads(print_queue_two, arguments.n_two_printers);
	
	if(arguments.verbose_mode == 2) printf("Joining printer1 threads\n");
	for(i=0; i<arguments.n_one_printers; i++)
	{
		err = pthread_join(pSpoolsOne[i], NULL);
		if(err != 0)
		{
			perror("failed joining threads");
			exit(-1);
		}
	}
	if(arguments.verbose_mode == 2) printf("Joining printer2 thread\n");
	for(i=0; i<arguments.n_two_printers; i++)
	{
		err = pthread_join(pSpoolsTwo[i], NULL);
		if(err != 0)
		{
			perror("failed joining threads");
			exit(-1);
		}
	}
	if(arguments.verbose_mode == 2) printf("Closing Log file\n");
	fclose(log_file);
	if(arguments.verbose_mode == 2) printf("Destroying printer1 queues\n");
	queue_destroy(print_queue_one);
	if(arguments.verbose_mode == 2) printf("Destroying printer2 queues\n");
	queue_destroy(print_queue_two);
	if(arguments.verbose_mode == 2) printf("Freeing memory and destroying mutex lock\n");
	print_job_destroy(mah_print_job); 
	free(str);
	free(t);
	pthread_mutex_destroy(&file_lock);
	return 0;
}
