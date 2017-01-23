library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

entity multiplier is
	port(
		a: in std_logic_vector(31 downto 0);
		b: in std_logic_vector(31 downto 0);
		p: out std_logic_vector(31 downto 0)
	);
end entity;

architecture beh of multiplier is
	signal p1 : std_logic_vector(63 downto 0);
begin
	p1 <= a * b;
	p <= p1(31 downto 0);
end beh;