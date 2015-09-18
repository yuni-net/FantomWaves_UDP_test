#include <iostream>
#include <FantomWaves.h>

int main()
{
	const unsigned short port = 31415;
	fw::Bindata data;
	data.add(char(0));
	data.add(int(31415));
	data.add(std::string("I'm finding the server"));
	const int limit_time = 2;
	fw::Bindata server_response;
	data.add(char(0));
	data.add(int(31415));
	data.add(std::string("I'm the server"));

	fw::UDP_cliant net;
	net.connect_server(port, data, limit_time, server_response);

	std::cout << "connecting to ther server. plz wait..." << std::endl;
	bool did_send = false;

	while (true)
	{
		if (net.did_timeout())
		{
			std::cout << "failed to connect to the server cuz timeout." << std::endl;
		}

		if (net.did_connect_server() == false)
		{
			// Nothing
		}
		else
		{
			while (net.are_there_any_left_datas())
			{
				fw::Bindata data;
				net.pop_received_data(data);
				data.show_cmd();
			}

			if (did_send == false)
			{
				net.send(data);
				did_send = true;
			}
		}
	}

	return 0;
}