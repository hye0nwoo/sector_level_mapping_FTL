#define is_mapping_table_full(bank)	(g_misc_meta[bank].free_blk_cnt == 1)	// is_full_all_blks(bank)와 같은 방식으로 하면 될듯 합니다
#define inc_map_blk_cnt(bank)  (g_misc_meta[bank].map_free_blk_cnt--)
#define dec_map_blk_cnt(bank)  (g_misc_meta[bank].map_free_blk_cnt++)

static void set_vsn(UINT32 const lsn, UINT32 const vsn)
{
  int map_addr;

	map_addr = CACHE_MAP_ADDR + find_caching_addr(bank);
  //update metadata
  //????

  write_dram_32(map_addr + (lsn % SECTORS_PER_PAGE) * sizeof(UINT32), vsn);
}


static UINT32 get_vsn(UINT32 const lsn)
{
  int map_addr;

	map_addr = CACHE_MAP_ADDR + find_caching_addr(bank);
  //update metadata
  //????

  return read_dram_32(map_addr + (lsn % SECTORS_PER_PAGE) * sizeof(UINT32));
}


static UINT32 find_caching_addr(UINT32 const bank)
{
	UINT32 addr;

	if(!is_mapping_table_cached(lsn))
  {
  	inc_map_blk_cnt(bank);

  	if(!is_mapping_table_full(bank))
  	{
  		flush_page(bank);	// 정책에 따라 victim page를 nand에 flush하는 함수, 민지누나가 짜셔야 할 부분
  	}
  }

  addr = free_page_addr(bank);	// caching mapping table을 관리하는 테이블로부터 free page addr을 반환하는 함수, 민지누나가 짜셔야 할 부분

	//update metadata
	dec_map_blk_cnt(bank);

	return  addr;
}


static int is_mapping_table_cached(UINT32 const lsn)
{
	if(mem_search_equ_dram(CACHE_LRU_ADDR, (?????), (????), (lsn / SECTORS_PER_PAGE) * SECTORS_PER_PAGE))
	{
		return true;
	}
	
	return false;
}