unsigned char start_meas( void );
void read_meas( void );
void search_rom(void);
void search(unsigned char *line_mask, unsigned char id[8]);
unsigned int search_free(unsigned char line_mask);
unsigned char comp(unsigned char id[8], unsigned int adr_s, unsigned int adr_end);
