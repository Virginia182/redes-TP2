double getTime(){ //retorna o tempo em double
	
	struct timeval now;
    int rc;
	double time_out;

    rc = gettimeofday(&now, NULL);
	
    if(rc == 0) {
		time_out = now.tv_sec + (now.tv_usec)/1000000.0;
    }
    else {
        printf("gettimeofday() failed, errno = %d\n", errno);
        return -1;
    }
	
	return time_out;
	
}
