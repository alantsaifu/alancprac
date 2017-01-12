#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <memory.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define SUCCESS   (0)
#define WRONG_PAR (-1)
#define WRONG_DEV (-2)
#define WRONG_BZ (-3)
#define WRONG_NONE (-4)

#define MOTOR_BZ (1)
#define MOTOR_AVLBL (0)

#define INFO_MOTOR_CREATE(fd, fd_status) do {\
    if ((fd = fopen("/run/spi_motor_info", "rb")) != NULL){\
        fd_status = SUCCESS;\
        fclose(fd);\
        fd = NULL;\
    }else{\
      if ((fd = fopen("/run/spi_motor_info", "wb+")) != NULL){\
        fd_status = SUCCESS;\
      }else{\
        fd_status = WRONG_DEV;\
      }\
    }\
  } while (0) 

#define INFO_MOTOR_READ(fd, num, a_info, i) do {\
    if ((fd = fopen("/run/spi_motor_info", "rb")) != NULL){\
        for(i=0; i<num; i++)\
            fread(a_info->m_info[i], sizeof(moto_info_t), 1, fd);\
        fclose(fd);\
        fd = NULL;\
    }\
  } while (0) 

#define INFO_MOTOR_WRITE(fd, num, a_info, i) do {\
    if ((fd = fopen("/run/spi_motor_info", "wb+")) != NULL){\
        for(i=0; i<num; i++)\
            fwrite(a_info->m_info[i], sizeof(moto_info_t), 1, fd);\
        fclose(fd);\
            fd = NULL;\
        }\
      } while (0)     

#define BUS_MOTOR_CREATE(fd, get_motor_exe, fd_status) do {\
    if ((fd = fopen("/run/spi_motor", "rb")) != NULL){\
        fread(&get_motor_exe, sizeof(get_motor_exe), 1, fd);\
        fd_status = SUCCESS;\
        fclose(fd);\
        fd = NULL;\
    }else{\
      if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){\
        fd_status = SUCCESS;\
      }else{\
        fd_status = WRONG_DEV;\
      }\
    }\
  } while (0) 

#define BUS_MOTOR_READ(fd, get_motor_exe, fd_status) do {\
      if ((fd = fopen("/run/spi_motor", "rb")) != NULL){\
        fread(&get_motor_exe, sizeof(get_motor_exe), 1, fd);\
        fd_status = SUCCESS;\
        fclose(fd);\
        fd = NULL;\
      }else{\
        fd_status = WRONG_DEV;\
      }\
  } while (0)

#define BUS_MOTOR_WRITE(fd, set_motor_exe, fd_status) do {\
        if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){\
            fwrite(&set_motor_exe, sizeof(set_motor_exe), 1, fd);\
            fd_status = SUCCESS;\
            fclose(fd);\
            fd = NULL;\
        }else{\
            fd_status = WRONG_DEV;\
        }\
    } while (0)

#define INIT_INFO(num, a_info, i) do {\
                a_info = (all_info*) malloc(sizeof(all_info));\
                if(a_info == NULL) {\
                    printf("[Error] a_info No enough space to allocate!\n%s\n",__func__);\
                }\
                for(num = 0; num < 5; num++) {\
                    a_info->m_info[num] = (moto_info_t*)malloc(sizeof(moto_info_t));\
                    if( a_info->m_info[num]== NULL) {\
                        for(i=0; i<num; i++)\
                            free(a_info->m_info[i]);\
                        free(a_info);\
                        printf("[Error] m_info %d No enough space to allocate!\n%s\n",num,__func__);\
                    }\
                }\
            } while (0)

#define DEINIT_INFO(num, a_info) do {\
              for(num = 0; num < 5; num++)\
                  free(a_info->m_info[num]);\
              free(a_info);\
          } while (0)  
		  
typedef struct {
  /* Motor position */
  int position;
  /* Limit sensor status */
  int l_sensor;
  /* Home sensor status */
  int h_sensor;
  /* Status of the action */
  int action;
  /* ID */
  int id;

} moto_info_t;

typedef struct {

  /* Suction pump status */
  int pump1;
  /* Dispense pump status */
  int pump2;

} pump_info_t;

typedef struct {

  /* Valve Suction status */
  int valve1;
  /* Valve Dispense status */
  int valve2;

} valve_info_t;

typedef struct {

  /* Home sensor status */
  int h_sensor;
  /* Status of the action */
  int action;

} bldc_info_t;

typedef struct {

  /* The heated status*/
  int h_status;
  /* The top cover heated */
  int top_h_sta;
  /* The under cover heated */
  int under_h_sta;

} heater_info_t;

typedef struct {

  /* the plate status */
  int s_plate;
  /* the door status */
  int s_door;

} doorplate_info_t;

typedef struct {

  pump_info_t *p_info;

  valve_info_t *v_info;

  moto_info_t *m_info[5];

  bldc_info_t *b_info;

  heater_info_t *h_info;

  doorplate_info_t *d_info;
 
} all_info;
        
#if 0
static int do_motor(void)
{
    //int i;
    FILE *fd = NULL;
    int set_motor_exe;
    int get_motor_exe;
    int fd_status = SUCCESS;

        BUS_MOTOR_READ(fd, get_motor_exe, fd_status);
        if(fd_status == WRONG_DEV)
            return WRONG_DEV;
           
        if(get_motor_exe){
            return WRONG_BZ;
        }

        set_motor_exe = MOTOR_BZ;
        BUS_MOTOR_WRITE(fd, set_motor_exe, fd_status);
        if(fd_status == WRONG_DEV)
            return WRONG_DEV;

        usleep(10000);

        set_motor_exe = MOTOR_AVLBL;
        BUS_MOTOR_WRITE(fd, set_motor_exe, fd_status);
        if(fd_status == WRONG_DEV)
            return WRONG_DEV;

    return SUCCESS;
}
#endif
 
int main() {
    //pid_t pid;
    FILE *fd = NULL;
    int num = 0;
    all_info *a_info;
    all_info b_info;
    int i;

    //int *pgmexe;
    //int get_motor_exe = 0;
    //int status;
    int fd_status = SUCCESS;

    //pgmexe = &get_motor_exe;

    INIT_INFO(num, a_info, i);

    INFO_MOTOR_CREATE(fd, fd_status);
    if(fd_status != SUCCESS)
        return WRONG_DEV;

    num = 5;
    INFO_MOTOR_READ(fd, num, a_info, i);  

    for(num=0; num<5; num++){
        printf("a_info->m_info[%d]->id = %d\r\n", num, a_info->m_info[num]->id);
        printf("a_info->m_info[%d]->position = %d\r\n", num, a_info->m_info[num]->position);
        printf("a_info->m_info[%d]->l_sensor = %d\r\n", num, a_info->m_info[num]->l_sensor);
        printf("a_info->m_info[%d]->h_sensor = %d\r\n", num, a_info->m_info[num]->h_sensor);
        printf("a_info->m_info[%d]->action = %d\r\n\r\n", num, a_info->m_info[num]->action);
    }

    for(num=0; num<5; num++){
        a_info->m_info[num]->id += 1;
        a_info->m_info[num]->position += 100;
        a_info->m_info[num]->l_sensor += 1;
        a_info->m_info[num]->h_sensor += 1;
        a_info->m_info[num]->action += 1;
    }

    memcpy(&b_info, a_info, sizeof(all_info));

    num = 5;
    INFO_MOTOR_WRITE(fd, num, a_info, i);
    
    DEINIT_INFO(num, a_info);

    return SUCCESS;
}

