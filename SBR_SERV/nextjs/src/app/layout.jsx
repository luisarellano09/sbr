
import "./globals.css";
import { Inter } from "next/font/google";

import {Providers} from "./providers";

import Layout from "@/components/NavLayout/Layout";


const inter = Inter({ subsets: ["latin"] });

export const metadata = {
	title: "SBR",
	description: "Self Balance Robot UI",
};

export default function RootLayout({ children }) {

    return (
        <html lang="en" className='mytheme'>
            <body>
                <Providers>
                    <Layout>
                        {children}
                    </Layout>
                </Providers>
            </body>
        </html>
    );
}
