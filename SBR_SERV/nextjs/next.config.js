/** @type {import('next').NextConfig} */
const nextConfig = {
    images: {
        domains: ["images.unsplash.com", "via.placeholder.com"],
    },
    env: {
        GRAPHQL_URL: process.env.GRAPHQL_URL,
      }
}

module.exports = nextConfig
