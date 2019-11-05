//ears.cpp

#include "ears.h"
//create a handler that will loop and listen for commands
//passing the recognized words to the logic node for processing

Ears::Ears()
{
	//this is a very basic langauge model that comes with pocketsphinx
	//use the setLMdir and setDICdir to set your own language models
	// CONFIG DE BASE
	std::string temp = MODELDIR;

	lmDir = temp  +"/lm/en/turtle.DMP";
	dicDir = temp +"/lm/en/turtle.dic";
	hmmDir = temp +"/hmm/en_US/hub4wsj_sc_8k";

	locFile = "out.raw";

}


Ears::Ears(std::string lang)
{
	std::string temp = MODELDIR;

	// CONFIG DE BASE
	lmDir = temp  +"/lm/en/turtle.DMP";
	dicDir = temp +"/lm/en/turtle.dic";
	hmmDir = temp +"/hmm/en_US/hub4wsj_sc_8k";

	// CONFIG FR
	if(lang == "FR")
	{
		lmDir = temp  +"/CMUS_FR/french3g62K.lm.dmp";
		dicDir = temp +"/CMUS_FR/frenchWords62K.dic";
		hmmDir = temp +"/CMUS_FR/lium_french_f0";
	}
	else if(lang == "FRmod")
	{
		lmDir = temp  +"/CMUS_FR_MOD/french3g62K.lm.dmp";
		dicDir = temp +"/CMUS_FR_MOD/frenchWords62K.dic";
		hmmDir = temp +"/CMUS_FR_MOD/lium_french_f0";
	}
	else if(lang == "EXP")
	{
		lmDir = temp  +"/lm/en/turtle.DMP";
		dicDir = temp +"/CMUS_FR_MOD/frenchWords62K.dic";
		hmmDir = temp +"/CMUS_FR_MOD/lium_french_f0";
	}

	locFile = "out.raw";

}


Ears::~Ears()
{
	//fclose(fh);
	Ears::close();
	ps_free(ps);

	// ajout
	delete fh;
}

//this will give us access to pocket sphinx's cmd_ln.c interpreter
int Ears::init()
{
	//create a config object
	config = cmd_ln_init(NULL, ps_args(), TRUE,
			     "-hmm", hmmDir.c_str(),
			     "-lm", lmDir.c_str(),
			     "-dict", dicDir.c_str(),
			     NULL);
	if (config == NULL)
		return 1;

	//initialize the decoder
	ps = ps_init(config);
	if (ps == NULL)
		return 1;


	if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"), (int)cmd_ln_float32_r(config, "-samprate"))) == NULL)
	{
		E_FATAL("Failed to open audio device\n");
		return 1;
	}

    /* Initialize continuous listening module */
    if ((cont = cont_ad_init(ad, ad_read)) == NULL)
    {
    	E_FATAL("Failed to initialize voice activity detection\n");
    	return 1;
	}
    if (ad_start_rec(ad) < 0)
    {
    	E_FATAL("Failed to start recording\n");
    	return 1;
	}
    if (cont_ad_calib(cont) < 0)
    {
    	E_FATAL("Failed to calibrate voice activity detection\n");
    	return 1;
	}

	return 0;
}

//the ability to set the location for the models will allow new models to be composed and replaced with ease
int Ears::setLMdir(std::string _lmDir)
{
	std::string temp = MODELDIR;

	lmDir = temp+ _lmDir;
	if(lmDir.c_str()==NULL)
		return -1;

	updateModel();//update the LM if config already exists
	return 1;
}

int Ears::setDICdir(std::string _dicDir)
{
	std::string temp = MODELDIR;

	dicDir = temp+ _dicDir;
	if(dicDir.c_str() ==NULL)
		return -1;

	updateModel(); //update Dictionary if config object already exists 
	return 1;
}


int Ears::updateModel()
{
	//if init has not been called we don't need to restart pocketSphinx
	if(config == NULL)
		return 1;

	ps_free(ps); //free the decoder
	Ears::close();

    return (init()); //call init to load the decoder with the new language model.

}
//use this for real time decoding via a microphone. Hardware settings are handled in the hardware node 
//and assigned through the logic node

/********************
	AMELIORATIONS
*********************/

std::string Ears::listenMicro()
{
        /* Indicate listening for next utterance */
        //printf("PRET A ECOUTER...\n");

        fflush(stdout);
        fflush(stderr);

        /* Wait data for next utterance */
        while ((k = cont_ad_read(cont, adbuf, 4096)) == 0)
            //sleep_msec(100);
        	system("sleep 0.1");

        if (k < 0)
            E_FATAL("Failed to read audio\n");
        /*
         * Non-zero amount of data received; start recognition of new utterance.
         * NULL argument to uttproc_begin_utt => automatic generation of utterance-id.
         */
        if (ps_start_utt(ps, NULL) < 0)
            E_FATAL("Failed to start utterance\n");
        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        //printf("ECOUTE EN COURS...\n");
        fflush(stdout);

        /* Note timestamp for this first block of data */
        ts = cont->read_ts;

        /* Decode utterance until end (marked by a "long" silence, >1sec) */
        for (;;) {
            /* Read non-silence audio data, if any, from continuous listening module */
            if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
                E_FATAL("Failed to read audio\n");
            if (k == 0) {
                /*
                 * No speech data available; check current timestamp with most recent
                 * speech to see if more than 1 sec elapsed.  If so, end of utterance.
                 */
                if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
                    break;
            }
            else {
                /* New speech data received; note current timestamp */
                ts = cont->read_ts;
            }

            /*
             * Decode whatever data was read above.
             */
            rem = ps_process_raw(ps, adbuf, k, FALSE, FALSE);

            /* If no work to be done, sleep a bit */
            if ((rem == 0) && (k == 0))
                //sleep_msec(20);
            	system("sleep 0.02");
        }

        /*
         * Utterance ended; flush any accumulated, unprocessed A/D data and stop
         * listening until current utterance completely decoded
         */
        ad_stop_rec(ad);
        while (ad_read(ad, adbuf, 4096) >= 0);
        cont_ad_reset(cont);

        printf("Ecoute terminée, Analyse en cours...\n");
        fflush(stdout);
        /* Finish decoding, obtain and print result */
        ps_end_utt(ps);
        hyp = ps_get_hyp(ps, NULL, &uttid);
        std::string MyWord = hyp;
        fflush(stdout);
        
        /* Resume A/D recording for next utterance */
        if (ad_start_rec(ad) < 0)
            E_FATAL("Failed to start recording\n");

        //std::cout << "\n\n\n" << std::endl;

        return MyWord;
}

void Ears::close()
{
	cont_ad_close(cont);
    ad_close(ad);	
}
