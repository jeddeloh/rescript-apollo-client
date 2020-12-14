import React from "react";
import clsx from "clsx";
import Layout from "@theme/Layout";
import Link from "@docusaurus/Link";
import useDocusaurusContext from "@docusaurus/useDocusaurusContext";
import useBaseUrl from "@docusaurus/useBaseUrl";
import styles from "./styles.module.css";

function Feature({ imageUrl, title, description }) {
  const imgUrl = useBaseUrl(imageUrl);
  return (
    <div className={clsx("col col--4", styles.feature)}>
      {imgUrl && (
        <div className="text--center">
          <img className={styles.featureImage} src={imgUrl} alt={title} />
        </div>
      )}
      <h3>{title}</h3>
      <p>{description}</p>
    </div>
  );
}

function Home() {
  const context = useDocusaurusContext();
  const { siteConfig = {} } = context;
  return (
    <Layout title={`Hello from ${siteConfig.title}`}>
      <header
        className={clsx("hero hero--primary white-bg", styles.heroBanner)}
      >
        <div className={styles.heroInner}>
          <img
            className={clsx("banner-img", styles.heroLogo)}
            src="img/logo.png"
          />
          <h1 className={styles.heroProjectTagline}>
            <p className="hero__subtitle purple-text">{siteConfig.tagline}</p>
          </h1>
          <div className={styles.index}>
            <Link
              className={styles.indexGetStartedButton}
              to={useBaseUrl("docs/")}
            >
              Get Started
            </Link>
            <span className={styles.indexGitHubButtonWrapper}>
              <iframe
                className={styles.indexGitHubButton}
                src="https://ghbtns.com/github-btn.html?user=reasonml-community&amp;repo=rescript-apollo-client&amp;type=star&amp;count=true&amp;size=large"
                width={160}
                height={30}
                title="GitHub Stars"
              />
            </span>
          </div>
        </div>
      </header>
    </Layout>
  );
}

export default Home;
