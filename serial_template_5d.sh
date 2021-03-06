#!/bin/bash -l

L=16
LX=${L}
LY=${L}
LZ=${L}
LT=${L}
LS=5

MPIX=1
MPIY=1
MPIZ=1
MPIT=1
MPIS=1

BETA=6.0
BETA_5="4.0 6.0 6.0 4.0 0.0"

#seed must be five, space separated integers
SEED_SERIAL="2 5 3 8 9"
SEED_PARALLEL="6 91 2 12 98"

TRAJ=100
THERM=10
SAVE=10
START=10

HMC_STEP_SIZE=20
HMC_TRAJ_LENGTH=1.0

LOG='Integrator'
START_TYPE='CheckpointStart'

COMMAND="./Test_hmc_WilsonGauge ${SEED_SERIAL} 
                                ${SEED_PARALLEL} 
				${BETA} 
                                ${BETA_5}
                                ${HMC_STEP_SIZE} 
                                ${HMC_TRAJ_LENGTH}
				--grid ${LX}.${LY}.${LZ}.${LT}.${LS} 
				--mpi ${MPIX}.${MPIY}.${MPIZ}.${MPIT}.${MPIS}
                                --threads ${OMP_NUM_THREADS} 
                                --SaveInterval ${SAVE}
	        	       	--Trajectories ${TRAJ} 
				--Thermalizations ${THERM} 
				--log ${LOG} "
#                                                  --StartingTrajectory ${START} --StartingType ${START_TYPE}"

echo ""
echo "Command given:"
echo ${COMMAND}
echo ""

${COMMAND}
