# 🪓 Remaining work
- [ ] TODO: SL in VSCode; SL in CLion (?)
  - Generate compilation database with `Bear make`
  - "Open folder" in VS Code (with SonarLine plugin installed). auto-configured the compilation DB produced by Bear
- [ ] TODO: quickfix
- [ ] TODO: SC autoscan
  - clone the repository, add it to SonarCloud. the autoscan should start and finish quickly
- [ ] TODO: SC CI-based. show the difference
  - prepare a branch with configured analysis, using build-wrapper.
    Also mention compilation database.
  - Show a new issue produced once the branch with analysis is merged and the GH Action finishes.
  - [ ] TODO: Coverage import
- [ ] TODO: PR analysis. CaYC
  - Prepare a PR with different issues.
    Demonstrate that the quality gate mentions only the the issues on the changed and added code.
    Explain CaYC
- [ ] TODO: Bug/Code-Smell/Vulnerability
  Demonstrate different kinds of findings. Difference between a Bug and a Code-Smell.
  Special workflow for a vulnerability
- [ ] TODO: issue with secondaries
  show the short-cut navigation
- [ ] TODO: single-flow issue
- [ ] TODO: multi-flow issue

# 📜 Storyboard

The goal of this demo is to show the analysis of a C++ application in SonarCloud.
We want to showcase how to apply the "Clean As You Code" methodology in practice.

We start with a legacy application.
This legacy application contains a "main" branch with the existing code.
It also contains an "add-feature" branch that represents a new feature we want to develop for the application.

The full set-up can either be done as part of the demo (takes about 15 minutes), or beforehand.
A branch "enable-ci-analysis" is available to move from Automatic Analysis to a CI-based analysis, with import of code coverage information.

Once the repository is fully set-up, you can observer the concept of PR Quality Gate on new code
and its independence from the main code issues.
The application features basic, yet varied, issue types that can be detected by SonarCloud. In the PR, we have:

[//]: # * A simple bug with no secondary locations

[//]: # * A bug with a secondary location in another file

[//]: # * A bug with an execution flow

[//]: # * A bug with multiple flows

[//]: # * A "bad practice" code smell

[//]: # * A stylistic code smell

Additionally, we have a security hotspot on the main branch:

[//]: # * A slow regular expression, vulnerable to catastrophic backtracking

When setting up CI-based analysis, import of code coverage will be done by default (in the "enable-ci-analysis" branch).

To demo SonarLint you can also clone this project to show the issues in SonarLint.
Some of the issues have quick fixes for them.

You can show the conected mode by simply following the tutorial in the IDE,
which allow to synchronize silenced issues/custom quality profiles/additional cross-TU issues.

# 🛠 Building and running the application

TODO

# 📝 Setup instructions

We are going to set up a SonarCloud analysis on this project.
We will visualise issues on the main branch and on pull requests and see how PRs get decorated automatically.

We will then set up a CI-based analysis and import code coverage information into the SonarCloud UI.

Useful link: https://docs.sonarcloud.io/

## 🛫 Getting Started

* Fork this project *with all branches* (not the default, only `main`).
* TODO: is a GitHub action necessary?
* Go to "Pull requests->New pull request" and opan a pull request from the
  `add-feature` branch to the `main` branch of your fork.
  Be careful: by default, the PR targets the upstream repository.
* TODO: Should a GitHub action run here?
* Go to https://sonarcloud.io/sessions/new and sign up with your GitHub account.
* Create a new organization under your name if there is none.
* Give SonarCloud permission to see the forked repository.

# 🎥 Demo

## 🤖 Automatic Analysis on SonarCloud

* Click ➕ in the top-right corner and select "Analyze new project"
* Select the forked repository.
* Click "Set Up"

## 👷 CI-based analysis on SonarCloud with coverage display

## ⚡ SonarLint: Fix issues before they exist

### 🦭 CLion

### ⌨ Visual Studio Code

### 📄 Show rule description

### 🪛 Quick Fix

### 🔌 Synchronize isues between SonarCloud and SonarLint

# 🛬 Teardown 

To prepare for the next demo, you should delete the project from SonarCloud:

* Open the demo-cpp project.
* Click on "Administration" in the bottom-left corner, and select "Deletion".
* click on "Delete" and confirm it by entering your project name.

You might also want to delete it from you GitHub account
At the bottom of this page: "https://github.com/<your-account>/cpp-demo/settings"
