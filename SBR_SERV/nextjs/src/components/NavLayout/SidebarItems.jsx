import { Accordion, AccordionItem } from "@nextui-org/react";
import Link from "next/link";
import {
    CalendarIcon,
    FolderIcon,
    HomeIcon,
    UserGroupIcon,
  } from "@heroicons/react/24/outline";

export default function SidebarItems({ collapsed }) {

	return (
		<main>
			<Accordion isCompact selectionMode="multiple" variant="light" defaultExpandedKeys={["1","2","3"]}
            itemClasses={{
                title: "font-bold text-medium text-indigo-100",
                content: "text-small px-2 text-indigo-100 border-b border-b-slate-700",
            }}>
				<AccordionItem
					key="1"
					aria-label="Accordion 1"
					title="Accordion 1"
                    startContent={  <CalendarIcon className="w-4" /> }
				>
					<Link href="/"> <p>PID</p> </Link>
                    <Link href="/"> <p>PID</p> </Link>
                    <Link href="/"> <p>PID</p> </Link>
				</AccordionItem>

				<AccordionItem
					key="2"
					aria-label="Accordion 2"
					title="Accordion 2"
				>
					Option
				</AccordionItem>

				<AccordionItem
					key="3"
					aria-label="Accordion 3"
					title="Accordion 3"
				>
					Option
				</AccordionItem>

			</Accordion>
		</main>
	);
}
