others => X"00000000"
    );

  
begin
  port_a: process (CLK)
  begin 
    if (CLK'event and CLK = '1') then 
      if EN_A = '1' then
        DO_A <= my_Rom(conv_integer(ADDR_A));
        if WEN_A = '1' then
          my_Rom(conv_integer(ADDR_A)) <= DI_A;
        end if;
      end if;
    end if;
  end process;


  port_b: process (CLK)
  begin 
    if (CLK'event and CLK = '1') then 
      if EN_B = '1' then
        DO_B <= my_Rom(conv_integer(ADDR_B));
      end if;
    end if;
  end process;


end architecture behavioral;
