import { Accordion, AccordionItem, Button } from "@nextui-org/react";
import Link from "next/link";
import {
    HomeIcon,
    CogIcon,
    CpuChipIcon,
    WrenchIcon,
    PaperAirplaneIcon,
    LinkIcon,
    CubeIcon
  } from "@heroicons/react/24/outline";

export default function SidebarItems({ collapsed }) {

	return (
		<main>
			<Accordion isCompact selectionMode="multiple" variant="light" defaultExpandedKeys={["1","2","3","4","5","6"]}
            itemClasses={{
                title: "font-bold text-medium text-indigo-100",
                content: "text-small text-indigo-100 border-b border-b-slate-700",
            }}>

                <AccordionItem key="1" title="SBR" startContent={ <HomeIcon className="w-4" /> } >
					<Link href="/"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Home</p> </Link>
				</AccordionItem>

                <AccordionItem key="2" title="Live" startContent={ <PaperAirplaneIcon className="w-4" /> } >
					<Link href="/Live/ESP32"> <p className=" px-2 rounded-lg hover:bg-[#697083]">ESP32</p> </Link>
				</AccordionItem>

				<AccordionItem key="3" title="Setup" startContent={ <CogIcon className="w-4" /> } >
					<Link href="/Setup/ESP32"> <p className=" px-2 rounded-lg hover:bg-[#697083]">ESP32</p> </Link>
                    <Link href="/Setup/PI"> <p className=" px-2 rounded-lg hover:bg-[#697083]">PI</p> </Link>
                    <Link href="/Setup/NX"> <p className=" px-2 rounded-lg hover:bg-[#697083]">NX</p> </Link>
				</AccordionItem>

                <AccordionItem key="4" title="Devices" startContent={ <CpuChipIcon className="w-4" /> } >
					<Link href="/Devices/ESP32"> <p className=" px-2 rounded-lg hover:bg-[#697083]">ESP32</p> </Link>
                    <Link href="/Devices/PI"> <p className=" px-2 rounded-lg hover:bg-[#697083]">PI</p> </Link>
                    <Link href="/Devices/NX"> <p className=" px-2 rounded-lg hover:bg-[#697083]">NX</p> </Link>
				</AccordionItem>

                <AccordionItem key="5" title="PID Tunning" startContent={ <WrenchIcon className="w-4" /> } >
					<Link href="/Tunning/Position"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Position</p> </Link>
                    <Link href="/Tunning/Angle"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Angle</p> </Link>
				</AccordionItem>

                <AccordionItem key="6" title="Utilities" startContent={ <CubeIcon className="w-4" /> } >
					<Link href="/Utilities/Portainer"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Portainer</p> </Link>
                    <Link href="/Utilities/Graphql"> <p className=" px-2 rounded-lg hover:bg-[#697083]">GraphQL</p> </Link>
				</AccordionItem>

                <AccordionItem key="7" title="Links" startContent={ <LinkIcon className="w-4" /> } >
                    <Link href="https://github.com/luisarellano09/sbr" target="_blank"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Github</p> </Link>
                    <Link href="https://sbrpi/sbr_portainer/" target="_blank"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Portainer</p> </Link>
                    <Link href="https://sbrpi/sbr_rabbitmq_management" target="_blank"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Rabbitmq</p> </Link>
                    <Link href="https://sbrpi/sbr_serv_graphql_playground" target="_blank"> <p className=" px-2 rounded-lg hover:bg-[#697083]">GraphQL</p> </Link>
				</AccordionItem>

			</Accordion>
		</main>
	);
}
