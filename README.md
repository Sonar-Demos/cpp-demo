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
A branch "enable-ci-analysis" is available to move from Automatic Analysis to a CI-based analysis,
with the import of code coverage information.

Once the repository is fully set up, you can observe the concept of PR Quality Gate on new code
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

You can show the connected mode by simply following the tutorial in the IDE,
which allows

- the synchronization of silenced issues,
- custom quality profiles, and
- additional cross-TU issues.

# 🛠 Building and running the application

TODO

# 📝 Setup instructions

We are going to set up a SonarCloud analysis on this project.
We will visualize issues on the main branch and on pull requests and see how PRs get decorated automatically.

We will then set up a CI-based analysis and import code coverage information into the SonarCloud UI.

Useful link: https://docs.sonarcloud.io/

## 🛫 Getting Started

* Fork this project *with all branches*
  (untick the default checkbox, "Copy the `main` branch only").
* TODO: is a GitHub action necessary?
* Go to "Pull requests->New pull request" and open a pull request from the
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

## 👷 CI-based analysis on SonarCloud with a coverage display

This step assumes you have added the project to SonarCloud and executed automatic analysis (see previous step).

For examples of CI-based analysis on other platforms, see https://github.com/sonarsource-cfamily-examples

* Click ⚙ "Administration" on the bottom-left and select "Analysis Method"
* Disable the "Automatic Analysis" switch.
* Generate a SonarCloud token:
  * Click on your profile picture in the top-right corner and select "My Account".
  * Select the "Security" tab.
  * Enter a token name (e.g. `cpp-demo`), and click on "Generate Token"
  * Copy the token to clipboard
* Enter the token to the repository secrets on GitHub
  * Select the ⚙ "Settings" tab of your repository
  * Select the "Secrets and variables"/"Actions" section
  * Click on "New Repository Secret"
  * Enter the name of the secret: `SONAR_TOKEN`
  * Paste the secret from the previous step.
  * Click "Add Secret".
* Checkout the `enable-ci-analysis` branch.
* In "sonar-project.properties" file change the `sonar.projectKey` and
  `sonar.organization` to use your organization name (your GitHub username).
* Commit, push, and merge the branch into `main` (careful: select yor fork as the target)
* After a couple of minutes, you should be able to see the analysis results on SonarCloud

Note that the total number of issues has reduced
because CI-based analysis analyses only the code you compile
in the configuration that you provide.
If a file is never compiled, it will not be analyzed, unlike with automatic analysis.

TODO: highlight an appearing issue and explain why

TODO: show coverage and explain why it has appeared

## ⚡ SonarLint: Fix issues before they exist

### 🦭 CLion

### ⌨ Visual Studio Code

### 📄 Show rule description

### 🪛 Quick Fix

### 🔌 Synchronize issues between SonarCloud and SonarLint

# 🛬 Teardown 

To prepare for the next demo, you should delete the project from SonarCloud:

* Open the demo-cpp project.
* Click on ⚙ "Administration" in the bottom-left corner, and select "Deletion".
* click on "Delete" and confirm it by entering your project name.

You might also want to delete it from your GitHub account
Click the button at the bottom of the ⚙ "Settings": `https://github.com/<your-account>/cpp-demo/settings`
