#define is_mapping_table_full(bank)	(g_misc_meta[bank].free_blk_cnt == 1)	// is_full_all_blks(bank)와 같은 방식으로 하면 될듯 합니다
#define inc_map_blk_cnt(bank)  (g_misc_meta[bank].map_free_blk_cnt--)
#define dec_map_blk_cnt(bank)  (g_misc_meta[bank].map_free_blk_cnt++)

static void set_vsn(UINT32 const lsn, UINT32 const vsn)
{
  int map_addr;

  if(!is_mapping_table_cached(lsn))
  {
  	inc_map_blk_cnt(bank);
  	if(!is_mapping_table_full(bank))
  	{
  		flush_page(bank);	//민지누나가 짜셔야 할 부분
  	}

  	map_addr = CACHE_MAP_ADDR + caching_table(bank);

  	

  } 

  //update metadata
  //????

  write_dram_32(map_addr + (lsn % SECTORS_PER_PAGE) * sizeof(UINT32), vsn);
}

static UINT32 get_vsn(UINT32 const lsn)
{
  int map_addr;

  if(!is_mapping_table_cached(lsn))
  {
  	inc_map_blk_cnt(bank);
  	if(!is_mapping_table_full(bank))
  	{
  		flush_page(bank);	//민지누나가 짜셔야 할 부분
  	}

  	map_addr = CACHE_MAP_ADDR + caching_table(bank);

  	

  }

  //update metadata
  //????

  return read_dram_32(map_addr + (lsn % SECTORS_PER_PAGE) * sizeof(UINT32));
}


static int is_mapping_table_cached(UINT32 const lsn)
{
	if(mem_search_equ_dram(CACHE_LRU_ADDR, (?????) , (????), (lsn / SECTORS_PER_PAGE) * SECTORS_PER_PAGE))
	{
		return true;
	}

	return false;
}


static void caching_table(UINT32 const bank)
{
	//?????

	//update metadata
	dec_map_blk_cnt(bank);
}
