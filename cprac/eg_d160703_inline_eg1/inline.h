inline int inc_inline(volatile int *j){

	for (;*j < 105; (*j)++){
        	//*j += 2;
        	(*j)++;
	}

	switch (*j){
        	case 1:
        		(*j)++;
        	break;
        
        	case 2:
        		(*j)++;
        	break;

        	default:
                        (*j)++;
        	break;
	}
	return (*j);
}
