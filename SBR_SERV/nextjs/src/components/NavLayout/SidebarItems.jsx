import { Accordion, AccordionItem, Button } from "@nextui-org/react";
import Link from "next/link";
import {
    HomeIcon,
    CogIcon,
    CpuChipIcon,
    WrenchIcon,
  } from "@heroicons/react/24/outline";

export default function SidebarItems({ collapsed }) {

	return (
		<main>
			<Accordion isCompact selectionMode="multiple" variant="light" defaultExpandedKeys={["1","2","3","4"]}
            itemClasses={{
                title: "font-bold text-medium text-indigo-100",
                content: "text-small text-indigo-100 border-b border-b-slate-700",
            }}>

                <AccordionItem key="1" title="SBR" startContent={  <HomeIcon className="w-4" /> } >
					<Link href="/"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Home</p> </Link>
				</AccordionItem>

				<AccordionItem key="2" title="Setup" startContent={  <CogIcon className="w-4" /> } >
					<Link href="/Setup/ESP32"> <p className=" px-2 rounded-lg hover:bg-[#697083]">ESP32</p> </Link>
                    <Link href="/Setup/PI"> <p className=" px-2 rounded-lg hover:bg-[#697083]">PI</p> </Link>
                    <Link href="/Setup/NX"> <p className=" px-2 rounded-lg hover:bg-[#697083]">NX</p> </Link>
				</AccordionItem>

                <AccordionItem key="3" title="Devices" startContent={  <CpuChipIcon className="w-4" /> } >
					<Link href="/Devices/ESP32"> <p className=" px-2 rounded-lg hover:bg-[#697083]">ESP32</p> </Link>
                    <Link href="/Devices/PI"> <p className=" px-2 rounded-lg hover:bg-[#697083]">PI</p> </Link>
                    <Link href="/Devices/NX"> <p className=" px-2 rounded-lg hover:bg-[#697083]">NX</p> </Link>
				</AccordionItem>

                <AccordionItem key="4" title="PID Tunning" startContent={  <WrenchIcon className="w-4" /> } >
					<Link href="/Tunning/Position"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Position</p> </Link>
                    <Link href="/Tunning/Angle"> <p className=" px-2 rounded-lg hover:bg-[#697083]">Angle</p> </Link>
				</AccordionItem>

			</Accordion>
		</main>
	);
}
